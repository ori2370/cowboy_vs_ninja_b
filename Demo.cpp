/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
using namespace std;

#include "sources/Team.hpp" //no need for other includes
#include "sources/SmartTeam.hpp"
#include "sources/Team2.hpp" //no need for other includes

using namespace ariel;

int main()
{
   Point a(32.3, 44), b(1.3, 3.5);
   assert(a.distance(b) == b.distance(a));
   Cowboy *tom = new Cowboy("Tom", a);
   OldNinja *sushi = new OldNinja("sushi", b);
   tom->shoot(sushi);
   cout << tom->print() << endl;

   sushi->move(tom);
   sushi->slash(tom);

   Team team_A(tom);
   cout << tom->print() << endl;

   team_A.add(new YoungNinja("Yogi", Point(64, 57)));
   cout << tom->print() << endl;

   // Team b(tom); should throw tom is already in team a

   SmartTeam team_B(sushi);
   team_B.add(new TrainedNinja("Hikari", Point(12, 81)));
   int round = 1;
   cout << "before attack" << endl;
   cout << "team A:" << endl;
   team_A.print();
   cout << "team B:" << endl;
   team_B.print();
   while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0)
   {
      team_A.attack(&team_B);
      if (team_B.stillAlive() == 0)
         break; // no need to attack back (team B is dead
      team_B.attack(&team_A);
      cout << "round " << round++ << endl;
      cout << "team A:" << endl;
      team_A.print();
      cout << "team B:" << endl;
      team_B.print();
   }

   if (team_A.stillAlive() > 0)
      cout << "winner is team_A" << endl;
   else
      cout << "winner is team_B" << endl;

   return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.
}
