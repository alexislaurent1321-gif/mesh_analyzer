#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <vector>

/**
 * @brief A struct representing a point in 3D space
 * 
 */
struct Point {
    float x, y, z; ///< Coordinates of the point


    /**
     * @brief Construct a new Point object at the origin
     * 
     */
    Point() : x(0), y(0), z(0) {}


    /**
     * @brief Construct a new Point object at the specified coordinates (z defaults to 0)
     * 
     * @param x_ 
     * @param y_ 
     */
    Point(float x_, float y_) : x(x_), y(y_), z(0) {}


    /**
     * @brief Construct a new Point object at the specified coordinates
     * 
     * @param x_ 
     * @param y_ 
     * @param z_ 
     */
    Point(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}


    /**
     * @brief Calculate the length of the vector from the origin to this point
     * 
     * @return float length of the vector
     */
    float length() const;


    Point operator-(const Point& other) const{
        return Point(x - other.x, y - other.y, z - other.z);
    }

    Point operator+(const Point& other) const{
        return Point(x + other.x, y + other.y, z + other.z);
    }

    Point operator*(float scalar) const {
        return Point(x * scalar, y * scalar, z * scalar);
    }

    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9 && std::abs(z - other.z) < 1e-9;
    }

    void operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }

    void operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }


    /**
     * @brief Calculate the distance between this point and another point
     * 
     * @param other 
     * @return float distance between the points
     */
    float distance(const Point& other) const;

    
    /**
     * @brief Overload the << operator to print the point's coordinates
     * 
     * @param os 
     * @param p 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif