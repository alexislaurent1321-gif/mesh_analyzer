#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

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

    /**
     * @brief Subtract another point from this point to get the vector between them
     * 
     * @param other 
     * @return Point resulting vector from the subtraction
     */
    Point operator-(const Point& other) const;

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