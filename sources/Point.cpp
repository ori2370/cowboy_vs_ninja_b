#include "Point.hpp"
#include <cmath>

using namespace std;
namespace ariel
{

    double Point::distance(const Point &other) const
    {
        double a = pow((other.x - this->x), 2); //(x2-x1)^2
        double b = pow((other.y - this->y), 2); //(y2-y1)^2
        return sqrt(a + b);
    }
    // took this from https://math.stackexchange.com/questions/2045174/how-to-find-a-point-between-two-points-with-given-distance
    Point Point::moveTowards(const Point &source, const Point &dest, double distance)
    {
        if (distance < 0)
        {
            throw invalid_argument("cant be negative");
        }
        double points_distance = source.distance(dest);
        if (points_distance <= distance)
        {
            // the closet point is the dest point.
            return dest;
        }
        double delta_x = dest.x - source.x;
        double delta_y = dest.y - source.y;
        double fixed_distance = distance / points_distance;
        double tempX = source.x + fixed_distance * (delta_x);
        double tempY = source.y + fixed_distance * (delta_y);
        return Point(tempX, tempY);
    }
    string Point::toString() const
    {
        string tmp = "(" + to_string(x) + "," + to_string(y) + ")";
        return tmp;
    }
}