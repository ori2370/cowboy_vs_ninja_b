#include "Character.hpp"

using namespace std;
namespace ariel
{
    Character::Character(string name, Point location, int hp) : name(name), location(location), hp(hp), has_team(false) {}
    Character::~Character() {}

    bool Character::isAlive() const
    {
        return 0 < hp;
    }
    double Character::distance(const Character *other) const
    {
        double distance = location.distance(other->location);
        return distance;
    }
    void Character::hit(int dmg)
    {
        if (dmg < 0)
        {
            throw invalid_argument("cant hit negative");
        }
        if (!isAlive())
        {
            throw invalid_argument("target is already dead!");
        }
        hp -= dmg;
        if (hp < 0)
        {
            hp = 0;
        }
    }

}