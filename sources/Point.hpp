#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>

using namespace std;
namespace ariel
{
    class Point
    {
        double x, y;

    public:
        Point(double x, double y) : x(x), y(y) {}

        double distance(const Point &other) const;
        static Point moveTowards(const Point &source, const Point &dest, double dist);
        // methods and functions
        string toString() const;
        double getX() const
        {
            return x;
        }
        double getY() const
        {
            return y;
        }
        void setX(double x)
        {
            this->x = x;
        }
        void setY(double y)
        {
            this->y = y;
        }
    };

}
#endif