#include "Ninja.hpp"

using namespace std;
namespace ariel
{
    // ctor and dtor
    Ninja::Ninja(string name, Point location, int hp, int agility) : Character(name, location, hp), agility(agility)
    {
        setType(NINJA);
    }
    Ninja::~Ninja() {}

    // methods and functions
    void Ninja ::move(Character *other)
    {
        // first check if can move
        if (!isAlive())
        {
            throw runtime_error("character already dead");
        }
        double distance = location.distance(other->getLocation());
        // check if the player can move all the distance
        if (distance <= agility)
        {
            Point tmp = location.moveTowards(location, other->getLocation(), distance);
            location = tmp;
        }
        else
        {
            Point tmp = location.moveTowards(location, other->getLocation(), agility);
            location = tmp;
        }
    }
    void Ninja::slash(Character *other)
    {
        // check if player able to use turn
        if (!isAlive())
        {
            throw runtime_error("character already dead");
        }
        // check if target is viable
        if (!other->isAlive())
        {
            throw runtime_error("target already is dead");
        }
        if (this == other)
        {
            throw runtime_error("self-harming not allowed");
        }
        // ninja can hit only if within range (1 meter)
        double distance = location.distance(other->getLocation());
        if (distance > 1)
        {
            return;
        }
        else
        {
            other->hit(40);
        }
    }
    void Ninja::performAttack(Character *other) // helper function use in Team only so no need to check if alive
    {
        double distance = location.distance(other->getLocation());
        if (distance > 1)
        {
            move(other);
            return;
        }
        slash(other);
    }
    string Ninja::print() const
    {
        string state_string = "N ";
        if (!isAlive())
        {
            state_string += "(" + name + ")";
        }
        else
        {
            state_string += name + " ,HP:" + to_string(hp) + " ,Location:" + location.toString();
        }

        return state_string;
    }
    /* string Ninja::toString() const
     {
         string state_string = "N ";
         if (!isAlive())
         {
             state_string += "(" + name + ")";
         }
         else
         {
             state_string += name + " ,HP:" + to_string(hp) + " ,Location:" + location.toString();
         }

         return state_string;
     } */
}