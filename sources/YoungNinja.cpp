#include "Ninja.hpp"
#include "YoungNinja.hpp"
#define HP 100
#define AGIL 14
using namespace std;
namespace ariel
{

    YoungNinja::YoungNinja(string name, Point location) : Ninja(name, location, HP, AGIL) {}

    YoungNinja::~YoungNinja() {}

}