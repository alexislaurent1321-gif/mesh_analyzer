#ifndef BASIC_SHAPES_H
#define BASIC_SHAPES_H


#include "mesh/mesh.h"

/** 
 * @brief Generate a grid of vertices
 * @param mesh The mesh to populate with vertices
 * @param Nx Number of vertices in the x-direction
 * @param Ny Number of vertices in the y-direction
 * @param Lx The length of the grid in the x-direction
 * @param Ly The length of the grid in the y-direction
 */
void generateGrid(Mesh<Triangle>& mesh, int Nx, int Ny, float Lx, float Ly);


/** 
 * @brief Generate random points within a bounding box
 * @param mesh The mesh to populate with vertices
 * @param N The number of random points to generate
 * @param Lx The width of the bounding box
 * @param Ly The height of the bounding box
 */
void generateRandomPoints(Mesh<Triangle>& mesh, int N, float Lx, float Ly);

#endif