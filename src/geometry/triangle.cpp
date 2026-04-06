#include "geometry/triangle.h"


bool Triangle::containsEdge(int v1, int v2) const {
    return (v[0] == v1 && v[1] == v2) || (v[1] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[2] == v2) || (v[2] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[0] == v2) || (v[0] == v1 && v[2] == v2);
}


bool Triangle::containsPoint(const std::vector<Point>& vertices,const Point& P) {

    // Get the vertices of the triangle
    Point A = vertices[v[0]];
    Point B = vertices[v[1]];
    Point C = vertices[v[2]];

    // Shift the points so that P is at the origin
    float ax = A.x - P.x;
    float ay = A.y - P.y;
    float bx = B.x - P.x;
    float by = B.y - P.y;
    float cx = C.x - P.x;
    float cy = C.y - P.y;

    // Calculate the determinant of the matrix formed by the shifted points
    float det31 = ax * ax + ay * ay;
    float det32 = bx * bx + by * by;
    float det33 = cx * cx + cy * cy;

    // If the determinant is positive, P is inside the circumcircle of triangle ABC
    float det = ax * (by * det33 - cy * det32) -
                ay * (bx * det33 - cx * det32) +
                det31 * (bx * cy - cx * by);

    return det > 1e-9; // Use a small epsilon to account for floating-point precision issues
}
