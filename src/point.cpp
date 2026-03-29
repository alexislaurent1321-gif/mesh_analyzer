#include "point.h"

float Point::length() const { 
    return std::sqrt(x*x + y*y + z*z); 
}

Point Point::operator-(const Point& other) const {
    return Point{x - other.x, y - other.y, z - other.z};
}

float Point::distance(const Point& other) const {
    return (*this - other).length();
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}