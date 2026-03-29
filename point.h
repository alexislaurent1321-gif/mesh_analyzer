#include <iostream>
#include <cmath>


// Point 3D : coordinates x, y, z
struct Point {
    float x, y, z;

    Point() : x(0), y(0), z(0) {}
    Point(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    float length() const { 
        return std::sqrt(x*x + y*y + z*z); 
    }

    Point operator-(const Point& other) const {
        return Point{x - other.x, y - other.y, z - other.z};
    }

    float distance(const Point& other) const {
        return (*this - other).length();
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return os;
    }
};
