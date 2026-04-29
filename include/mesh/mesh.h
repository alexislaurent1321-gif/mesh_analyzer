#ifndef MESH_H
#define MESH_H

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
#include "geometry/triangle.h"
#include "geometry/tetrahedron.h"



/**
 * @brief A class representing a 3D mesh
 * 
 */
template <typename ElementType>
struct Mesh {

    // Datas
    std::vector<Point> vertices;            ///< List of vertices in the mesh
    std::vector<ElementType> elements;      ///< List of elements defined by vertex indices
    std::vector<float> ratios;              ///< aspect ratios of elements (for quality analysis)
};

#endif
