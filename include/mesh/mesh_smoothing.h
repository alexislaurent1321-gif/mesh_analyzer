#ifndef MESH_SMOOTHING_H
#define MESH_SMOOTHING_H

#include "mesh/mesh.h"
#include "mesh/mesh_analysis.h"

/** 
 * @brief Smooth the mesh by iteratively moving each vertex towards the centroid of its neighbors
 * @param iterations Number of smoothing iterations to perform
 * @param lambda Smoothing parameter (0 < lambda < 1)
 */
void smooth(Mesh<Triangle>& mesh, int iterations, float lambda);

#endif