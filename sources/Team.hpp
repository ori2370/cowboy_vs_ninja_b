#ifndef TEAM_HPP
#define TEAM_HPP
#include <iostream>
#include <vector>
#include "Character.hpp"
#include "Ninja.hpp"
#include "Cowboy.hpp"
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#define MAX_SIZE 10

using namespace std;

namespace ariel
{
    class Team
    {
    protected:
        vector<Character *> team_members;
        Character *team_leader;
        // helper methods:
        bool newTeamLeader();
        Character *findTarget(Team *other);

    public:
        Team(Character *team_leader);
        virtual ~Team();
        virtual void add(Character *member);
        virtual void attack(Team *other);
        int stillAlive();
        void print();
        vector<Character *> &getTeamMembers()
        {
            return team_members;
        }
    };
}

#endif