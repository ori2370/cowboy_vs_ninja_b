#include "Team.hpp"
#include <limits>
using namespace std;
namespace ariel
{
    Team::Team(Character *leader) : team_leader(leader)
    {
        if (leader->hasTeam())
        {
            throw runtime_error("player is already in a team");
        }
        team_members.push_back(leader);
        leader->setHasTeam(true);
    }
    Team::~Team()
    {
        for (Character *member : team_members)
        {
            delete member;
        }
    }

    bool Team::newTeamLeader()
    { // max so it will be change within the first alive member (as any number<max)
        double curr_distance = numeric_limits<double>::max();
        double distance = 0;
        Character *tmp = NULL;
        for (const auto &member : team_members)
        {
            if (member->isAlive())
            {
                distance = team_leader->distance(member);
                if (distance < curr_distance)
                {
                    tmp = member;
                    curr_distance = distance;
                }
            }
        }

        if (!tmp)
        {
            return false;
        }
        team_leader = tmp;
        return true;
    }
    Character *Team::findTarget(Team *other)
    {
        Character *newTarget = NULL;
        double curr_distance = numeric_limits<double>::max();
        double distance = 0;
        for (const auto &target : other->team_members)
        {
            if (target->isAlive())
            {
                distance = team_leader->distance(target);
                if (distance < curr_distance)
                {
                    curr_distance = distance;
                    newTarget = target;
                }
            }
        }
        return newTarget;
    }

    void Team::add(Character *member)
    {
        if (member->hasTeam())
        {
            throw runtime_error("player is already in a team");
        }
        if (team_members.size() >= MAX_SIZE)
        {
            throw runtime_error("team is already full");
        }
        if (member->getType() == COWBOY)
        {
            team_members.insert(team_members.begin(), member);
        } // we want cowboys to be first in line
        else
        {
            team_members.push_back(member);
        }

        member->setHasTeam(true);
    }
    void Team::attack(Team *other)
    {
        if (other == NULL || this == other)
        {
            throw invalid_argument("other team is not valid");
        }
        if (other->stillAlive() == 0)
        {
            throw runtime_error("target team is dead");
        }
        if (!(team_leader->isAlive()))
        {
            if (!newTeamLeader())
            {
                throw runtime_error("everyone it the team is dead");
            }
        }
        // will not be null as other.stillAlive >0
        Character *target = findTarget(other);
        for (const auto &ally_member : team_members)
        {
            if (ally_member->isAlive())
            {
                if (target->isAlive())
                {
                    ally_member->performAttack(target);
                }
                else
                {
                    target = findTarget(other);
                    if (target == nullptr)
                    { // all enemeis are dead
                        return;
                    }
                    else
                    {
                        ally_member->performAttack(target);
                    }
                }
            }
        }
    }
    int Team::stillAlive()
    {
        int count = 0;
        for (Character *member : team_members)
        {
            if (member->isAlive())
            {
                count++;
            }
        }
        return count;
    }

    void Team::print()
    {
        for (const auto &member : team_members)
        {
            cout << member->print() << endl;
        }
    }

}
