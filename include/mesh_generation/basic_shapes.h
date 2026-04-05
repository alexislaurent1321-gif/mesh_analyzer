#include "geometry/mesh.h"

/** 
 * @brief Generate a grid of vertices
 * @param mesh The mesh to populate with vertices
 * @param Nx Number of vertices in the x-direction
 * @param Ny Number of vertices in the y-direction
 * @param Lx The length of the grid in the x-direction
 * @param Ly The length of the grid in the y-direction
 */
void generateGrid(Mesh& mesh, int Nx, int Ny, float Lx, float Ly);