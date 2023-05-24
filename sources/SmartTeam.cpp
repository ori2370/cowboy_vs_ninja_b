#include "SmartTeam.hpp"
#include <limits>

using namespace std;
namespace ariel
{
    SmartTeam::SmartTeam(Character *team_leader) : Team(team_leader)
    {
    }

    SmartTeam::~SmartTeam() {}

    void SmartTeam::add(Character *member)
    {
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

    // first ninjas will attack if they are close to enemy, after it cowboys will attack lowest hp enemy, after it will move to the closest enemy
    // helper methods:
    Character *SmartTeam::ninjaViableTrgt(Character *player, Team *other)
    {
        Character *newTarget = NULL;
        for (const auto &enemy : other->getTeamMembers())
        {
            if (enemy->isAlive())
            {
                double distance = player->distance(enemy);
                if (distance <= 1)
                {
                    newTarget = enemy;
                }
            }
        }
        return newTarget;
    }
    Character *SmartTeam::cowboyTarget(Team *other)
    {
        Character *newTarget = NULL;
        for (const auto &enemy : other->getTeamMembers())
        {
            if (enemy->isAlive())
            {
                if (newTarget == NULL)
                {
                    newTarget = enemy;
                }
                else if (enemy->getHp() < newTarget->getHp())
                {
                    newTarget = enemy;
                }
            }
        }
        return newTarget;
    }
    Character *SmartTeam::ninjaTarget(Character *ninja, Team *enemy)
    { // like the findTarget method in Team.cpp
        Character *newTarget = NULL;
        double curr_distance = numeric_limits<double>::max();
        double distance = 0;
        for (const auto &target : enemy->getTeamMembers())
        {
            if (target->isAlive())
            {
                distance = ninja->distance(target);
                if (distance < curr_distance)
                {
                    curr_distance = distance;
                    newTarget = target;
                }
            }
        }
        return newTarget;
    }

    void SmartTeam::attack(Team *other)
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
                throw runtime_error("everyone in the team is dead");
            }
        }
        // will not be null as other.stillAlive >0
        // ninjas will attack first if there are enemies in range
        Character *viableTarget = NULL;
        for (auto &member : team_members)
        {
            if (member->getType() == NINJA && member->isAlive())
            {
                viableTarget = ninjaViableTrgt(member, other);
                if (viableTarget != NULL)
                {
                    member->performAttack(viableTarget);
                    member->setHasAttacked(true);
                }
            }
        }
        // ninjas attacked all the targets that are viable this round
        //  now cowboys will attack
        Character *target = cowboyTarget(other);
        for (auto &member : team_members)
        {
            if (member->getType() == COWBOY && member->isAlive())
            {
                if (target != NULL) // if not null he is alive
                {
                    member->performAttack(target);
                    member->setHasAttacked(true); // not needed
                }
                else
                {
                    target = cowboyTarget(other);
                    if (target != NULL)
                    {
                        member->performAttack(target);
                        member->setHasAttacked(true);
                    }
                }
            }
        }
        // all the cowboys attacked, now the remain ninjas will attack;
        for (auto &member : team_members)
        {
            if ((member->getType() == NINJA) && (member->isAlive()) && ((member->getHasAttacked() == false)))
            {
                Character *target = ninjaTarget(member, other);
                if (target != NULL) // if not found a target, means all the enemies are dead
                {
                    member->performAttack(target);
                    member->setHasAttacked(true);
                }
            }
        }
        // attack() is done all team members should have hasAttacked = true
        for (auto &member : team_members)
        {
            member->setHasAttacked(false);
        }
    }
}