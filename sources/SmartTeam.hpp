#ifndef SMARTTEAM_HPP
#define SMARTTEAM_HPP
#include "Team.hpp"

using namespace std;

namespace ariel
{
    class SmartTeam : public Team
    {
    private:
        // helper methods:
        Character *ninjaViableTrgt(Character *player, Team *other); // if ninja within range to attack
        Character *ninjaTarget(Character *player, Team *other);
        Character *cowboyTarget(Team *other); // if both wont be viable then they will attack like team1&2

    public:
        SmartTeam(Character *team_leader);
        ~SmartTeam();
        void add(Character *member);
        void attack(Team *other);
    };

}
#endif