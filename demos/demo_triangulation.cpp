#include <iostream>

#include "mesh/mesh.h"
#include "mesh/mesh_analysis.h"
#include "mesh/mesh_smoothing.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_triangulation.h"
#include "mesh/mesh_refine.h"


/** @file triangulation.cpp
 * @brief A simple demo to generate a grid mesh, perform Delaunay triangulation on it, analyze the resulting mesh, and export it to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    // Triangulation test on a grid

    // Example of generating a grid mesh and exporting it
    Mesh gridMesh;
    generateGrid(gridMesh, 5, 5, 1.f, 1.f);

    triangulate(gridMesh); // Perform Delaunay triangulation on the grid mesh

    analyzeMesh(gridMesh);
    exportToVTK("output.vtk", gridMesh);

    return 0;
}

