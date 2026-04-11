#include <iostream>

#include "mesh.h"
#include "analysis.h"
#include "smoothing.h"
#include "visualization/exportToVTK.h"
#include "processing/triangulation.h"


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

