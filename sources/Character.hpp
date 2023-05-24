#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Point.hpp"
#include <stdio.h>
#define COWBOY 1
#define NINJA 2

using namespace std;
namespace ariel
{

    class Character
    {
    protected:
        Point location;
        int hp;
        string name;
        bool has_team;
        int player_type;
        bool has_attacked = false; // only for SmartTeam

    public:
        // ctor and dtor
        Character(string name, Point location, int hp);
        virtual ~Character();
        // methods and functions
        virtual bool isAlive() const;
        virtual double distance(const Character *other) const;
        virtual void hit(int dmg);
        virtual void performAttack(Character *other) = 0; // abstract method
        // getters are the same on the derived class so no virtual
        string getName() const { return name; }
        Point getLocation() const { return location; }
        int getHp() const { return hp; }
        int getType()
        {
            return player_type;
        }
        bool hasTeam()
        {
            return has_team;
        }
        void setType(int type)
        {
            player_type = type;
        }

        // helper functions
        void setHasTeam(bool hasteam)
        {
            has_team = hasteam;
        }
        bool getHasAttacked()
        {
            return has_attacked;
        }
        void setHasAttacked(bool has_attacked)
        {
            this->has_attacked = has_attacked;
        }
        virtual string print() const = 0; // abstract method
    };
}

#endif