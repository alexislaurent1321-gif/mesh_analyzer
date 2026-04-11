#include "mesh.h"
#include "analysis.h"

/** 
 * @brief Smooth the mesh by iteratively moving each vertex towards the centroid of its neighbors
 * @param iterations Number of smoothing iterations to perform
 * @param lambda Smoothing parameter (0 < lambda < 1)
 */
void smooth(Mesh& mesh, int iterations, float lambda);