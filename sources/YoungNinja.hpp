#ifndef YOUNGNINJA_HPP
#define YOUNGNINJA_HPP

#include "Ninja.hpp"
using namespace std;

namespace ariel
{
    class YoungNinja : public Ninja
    {
    public:
        YoungNinja(string name, Point location);
        ~YoungNinja();
    };

}
#endif