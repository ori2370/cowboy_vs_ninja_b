#ifndef TEAM2_HPP
#define TEAM2_HPP
#include "Team.hpp"

using namespace std;

namespace ariel
{
    class Team2 : public Team
    {
    public:
        Team2(Character *team_leader);
        ~Team2();
        void add(Character *member);
    };

}
#endif