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



/**
 * @brief A class representing a 3D mesh
 * 
 */
class Mesh {
public:
    // Datas
    std::vector<Point> vertices;        ///< List of vertices in the mesh
    std::vector<Triangle> triangles;    ///< List of triangles defined by vertex indices
    std::vector<float> ratios;          ///< aspect ratios of triangles (for quality analysis)

    
/**
 * @brief  Load a mesh from an OBJ file using tinyobjloader
 * 
 * @param path Path to the OBJ file to load 
 * @return true 
 * @return false 
 */
bool loadObj(const std::string& path);

};

#endif
