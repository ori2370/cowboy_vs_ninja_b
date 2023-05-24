#ifndef NINJA_HPP
#define NINJA_HPP

#include "Character.hpp"
using namespace std;

namespace ariel
{
    // will act as abstarct/SUB class
    class Ninja : public Character
    {
    protected:
        int agility;
        Ninja(string name, Point location, int hp, int agility);

    public:
        // ctor and dtor
        virtual ~Ninja();
        // methods and functions
        void move(Character *other);
        void slash(Character *other);
        void performAttack(Character *other);
        string print() const;
        int getAgility() const
        {
            return agility;
        }
        // string toString() const;
    };

}

#endif