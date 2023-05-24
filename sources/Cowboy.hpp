#ifndef COWBOY_HPP
#define COWBOY_HPP
#include "Character.hpp"
using namespace std;

namespace ariel
{

    class Cowboy : public Character
    {
    private:
        int ammo;

    public:
        // ctor and dtor
        Cowboy(string name, Point location);
        ~Cowboy();
        // methods and functions
        void shoot(Character *other);
        bool hasboolets();
        void reload();
        string print() const;
        void performAttack(Character *other);
        int getAmmo() const
        {
            return ammo;
        }
        // string toString() const;
    };

}

#endif