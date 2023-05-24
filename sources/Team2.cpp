
#include "Team2.hpp"

using namespace std;
namespace ariel
{
    Team2::Team2(Character *team_leader) : Team(team_leader)
    {
    }

    Team2::~Team2() {}

    void Team2::add(Character *member)
    {
        if (member->hasTeam())
        {
            throw runtime_error("player is already in a team");
        }
        if (team_members.size() >= MAX_SIZE)
        {
            throw runtime_error("team is already full");
        }
        team_members.push_back(member);
        member->setHasTeam(true);
        // adding them in order of addition and not by type!
    }
}