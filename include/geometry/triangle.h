#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>


#include "geometry/point.h"
#include "geometry/edge.h"

/**
 * @brief A struct representing a triangle in the mesh
 * 
 */
struct Triangle {

    std::array<int, 3> v;   ///< Indices of the vertices that form the triangle
    bool isBad = false;     ///< Flag used in Delaunay triangulation to mark triangles that need to be removed
    

    /**
     * @brief  Check if the triangle contains a specific edge defined by two vertex indices
     * @param v1 index of the first vertex of the edge
     * @param v2 index of the second vertex of the edge
     */
    bool containsEdge(int v1, int v2) const;


    /** 
     * @brief Check if the triangle contains a specific point
     * @param vertices The list of vertices in the mesh
     * @param P The point to check
     * @return true if P is inside the triangle, false otherwise
     */
    bool containsPoint(const std::vector<Point>& vertices, const Point& P);

};