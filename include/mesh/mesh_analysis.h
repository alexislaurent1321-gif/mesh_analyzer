#ifndef QUALITY_H
#define QUALITY_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

#include "mesh/mesh.h"

// Quality analysis

/** 
 * @brief   Calculate the aspect ratio of a triangle defined by its vertex indices. An aspect ratio near to 1 indicates a more equilateral triangle
 * 
 * @param t 
 * @return float 
 */
float calculateAspectRatio(const Mesh<Triangle>& mesh, const Triangle& t);


/**
 * @brief  Calculate the aspect ratio for all triangles in the mesh and store them in the ratios vector
 * 
 */
void calculateAspectRatios(Mesh<Triangle>& mesh);



// Topology analysis

 /**
 * @brief Get the Edge Valences object  
 * 
 * @return std::unordered_map<Edge, int, EdgeHash> 
 */
std::unordered_map<Edge, int, EdgeHash> getEdgeValences(const Mesh<Triangle>& mesh);


 /** 
 * @brief Get the boundary edges of the mesh
 * @return A vector containing the boundary edges
 */
std::vector<Edge> getBoundaryEdges(const Mesh<Triangle>& mesh);


 /**
 * @brief Count the number of unique edges in the mesh by iterating through all triangles and adding their edges to an unordered_set
 * 
 * @return number of unique edges in the mesh 
 */
size_t countUniqueEdges(const Mesh<Triangle>& mesh);



// Display analysis

/**
 * @brief  Analyze the mesh by printing out the number of vertices, triangles, and unique edges. Optionally, it could also calculate and print the aspect ratio of each triangle for quality analysis.
 * 
 */
void analyzeMesh(Mesh<Triangle>& mesh);


#endif  