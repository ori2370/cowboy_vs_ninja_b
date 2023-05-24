#include "Ninja.hpp"
#include "TrainedNinja.hpp"
#define HP 120
#define AGIL 12
using namespace std;
namespace ariel
{

    TrainedNinja::TrainedNinja(string name, Point location) : Ninja(name, location, HP, AGIL) {}

    TrainedNinja::~TrainedNinja() {}

}