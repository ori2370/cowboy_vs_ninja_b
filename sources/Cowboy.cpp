#include "Cowboy.hpp"
#define HP 110
#define AMMO 6
using namespace std;
namespace ariel
{
    Cowboy::Cowboy(string name, Point location) : Character(name, location, HP), ammo(AMMO)
    {
        setType(COWBOY);
    }
    // has fixed number of muniation and HP
    Cowboy::~Cowboy() {}

    // methods and functions
    void Cowboy::shoot(Character *other)
    {
        // first check if the charactor can shot
        if (!isAlive())
        {
            throw runtime_error("the shooter is already dead\n");
        }
        if (!other->isAlive())
        {
            throw runtime_error("target is already dead");
        }
        if (this == other)
        {
            throw runtime_error("self-harming not allowed");
        }
        if (!hasboolets())
        { // cant shot without boolets;
            return;
        }
        // else no problem occured can shot
        other->hit(10); // bulzeye
        ammo--;
    }
    bool Cowboy::hasboolets()
    {
        return (ammo > 0);
    }
    void Cowboy::reload()
    {
        if (!isAlive())
        {
            throw runtime_error("cant reload if dead");
        }
        ammo = AMMO;
    }
    void Cowboy::performAttack(Character *other)
    {
        if (!hasboolets())
        {
            reload();
            return;
        }
        shoot(other);
    }

    string Cowboy::print() const
    {
        string state_string = "C ";
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
    /*
        string Cowboy ::toString() const
        {
            string state_string = "C ";
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
