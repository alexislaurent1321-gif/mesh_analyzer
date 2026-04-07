#include "geometry/point.h"

float Point::length() const { 
    return std::sqrt(x*x + y*y + z*z); 
}


float Point::distance(const Point& other) const {
    return (*this - other).length();
}


Point Point::operator-(const Point& other) const{
    return Point(x - other.x, y - other.y, z - other.z);
}

Point Point::operator+(const Point& other) const{
    return Point(x + other.x, y + other.y, z + other.z);
}

Point Point::operator*(float scalar) const {
    return Point(x * scalar, y * scalar, z * scalar);
}

bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9 && std::abs(z - other.z) < 1e-9;
}

void Point::operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

void Point::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

void Point::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}


std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}