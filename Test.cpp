#include "doctest.h"
#include "sources/Team.hpp"
#include <iostream>
using namespace std;
using namespace ariel;

TEST_CASE("Point methods")
{

    Point a(14.3, 23), b(14, 12.5);
    CHECK(a.distance(b) == b.distance(a));
    CHECK(a.moveTowards(a, b, 10).toString() == "(14.014402,13.004079)");
    CHECK_THROWS(a.moveTowards(a, b, -550));
}

TEST_CASE("charcters methods")
{
    Point a(14.3, 23), b(14, 12.5);
    Cowboy *yushi = new Cowboy("yushi", a);
    OldNinja *samurai = new OldNinja("samurai", b);
    SUBCASE("prints correctly")
    {
        CHECK(yushi->print() == "C yushi ,HP:110 ,Location:(14.300000,23.000000)");
        CHECK(samurai->print() == "N samurai ,HP:150 ,Location:(14.000000,12.500000)");
    }
    SUBCASE("shoots correctly")
    {
        CHECK(yushi->getHp() == 110);
        CHECK(samurai->getHp() == 150);
        for (int i = 0; i < 17; i++)
        {
            if (yushi->hasboolets())
            {
                yushi->shoot(samurai);
            }
            else
            {
                yushi->reload();
            }
        } // samurai should be dead 3times to reload +15 shots
        CHECK(samurai->isAlive() == false);
        CHECK(samurai->getHp() == 0);
        CHECK(samurai->print() == "N (samurai)");
        // check if cant hit dead or cant dead hit another
        CHECK_THROWS(yushi->shoot(samurai));
        CHECK_THROWS(samurai->slash(yushi));
    }
    SUBCASE("slash correctly")
    {
        samurai->slash(yushi); // not suppsed to be in range to hit yushi
        CHECK(yushi->getHp() == 110);
        while (samurai->getLocation().distance(yushi->getLocation()) > 1)
        {
            samurai->move(yushi);
        }
        samurai->slash(yushi); // supposed to hit yushi
        CHECK(yushi->getHp() == 70);
        samurai->slash(yushi);
        samurai->slash(yushi);
        CHECK(yushi->isAlive() == false);
        CHECK(yushi->getHp() == 0);
        CHECK(yushi->print() == "C (yushi)");
        // check if cant hit dead or cant dead hit another
        CHECK_THROWS(samurai->slash(yushi));
        CHECK_THROWS(yushi->shoot(samurai));
    }
    SUBCASE("cant hit themselvs")
    {
        CHECK_THROWS(yushi->shoot(yushi));
        CHECK_THROWS(samurai->slash(samurai));
    }
    delete yushi;
    delete samurai;
}
TEST_CASE("Team functionality")
{
    Point a(14.3, 23), b(14, 12.5);
    Cowboy *yushi = new Cowboy("yushi", a);
    OldNinja *samurai = new OldNinja("samurai", b);
    Team team_A(yushi);
    Team team_B(samurai);

    SUBCASE("Add members and print")
    {
        YoungNinja *yogi = new YoungNinja("Yogi", Point(64, 57));
        team_A.add(yogi);
        team_A.print();
        CHECK(team_A.stillAlive() == 2);
        team_B.add(new TrainedNinja("Hikari", Point(12, 81)));
        team_B.print();
        CHECK(team_B.stillAlive() == 2);
        // check if can add a player that is already in that team or in another team
        CHECK_THROWS(team_A.add(yushi));
        CHECK_THROWS(team_B.add(yushi));

        // check if max size can be greater than 10:
        for (int i = 0; i < 8; i++)
        {
            team_A.add(new YoungNinja("Yogi", Point(64, 57)));
        }
        CHECK(team_A.stillAlive() == 10);
        CHECK_THROWS(team_A.add(new YoungNinja("Yogi", Point(64, 57))));
    }
    SUBCASE("Attack other team")
    {
        team_A.add(new YoungNinja("Yogi", Point(64, 57)));
        team_B.add(new TrainedNinja("Hikari", Point(12, 81)));
        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0)
        {
            team_A.attack(&team_B);
            team_B.attack(&team_A);
        }
        /// if both dont work, attack() is not working
        bool a = (team_A.stillAlive() == 0 && team_B.stillAlive() > 0) || (team_A.stillAlive() > 0 && team_B.stillAlive() == 0);
        CHECK(a);
        // checking if dead team can attack other team and if team can attack dead team
        CHECK_THROWS(team_A.attack(&team_B));
        CHECK_THROWS(team_B.attack(&team_A));
    }
    SUBCASE("team attack throws")
    {
        CHECK_THROWS(team_A.attack(nullptr));
        CHECK_THROWS(team_A.attack(&team_A));
    }
}