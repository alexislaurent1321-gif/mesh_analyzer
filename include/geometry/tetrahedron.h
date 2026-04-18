#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

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

struct Tetrahedron {

    static constexpr size_t elementType = 4; ///< Gmsh element type for tetrahedra 
    static constexpr size_t numVertices = 4; ///< Number of vertices in a tetrahedron

    std::array<size_t, 4> v;   ///< Indices of the vertices that form the tetrahedron
    bool isBad = false;     ///< Flag used in Delaunay triangulation to mark tetrahedra that need to be removed


    /**
     * @brief Check if the circumsphere of the tetrahedron contains a specific point
     * @param vertices The list of vertices in the mesh
     * @param P The point to check
     * @return true if P is inside the circumsphere, false otherwise
     */
    bool containsPoint(const std::vector<Point>& vertices, const Point& P);


    /**
     * @brief Check if the circumsphere of the tetrahedron contains a specific edge defined by two vertex indices
     * @param v1 index of the first vertex of the edge
     * @param v2 index of the second vertex of the edge
     */
    bool containsEdge(int v1, int v2) const;
};

#endif 