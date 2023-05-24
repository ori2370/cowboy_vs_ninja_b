#include "Ninja.hpp"
#include "OldNinja.hpp"
#define HP 150
#define AGIL 8
using namespace std;
namespace ariel
{

    OldNinja::OldNinja(string name, Point location) : Ninja(name, location, HP, AGIL) {}

    OldNinja::~OldNinja() {}

}