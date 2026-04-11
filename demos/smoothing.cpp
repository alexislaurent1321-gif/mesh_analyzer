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
    Mesh irregularMesh;
    generateRandomPoints(irregularMesh, 25, 1.f, 1.f);

    triangulate(irregularMesh); // Perform Delaunay triangulation on the grid mesh

    smooth(irregularMesh, 100, 1.f); // Apply smoothing to improve triangle quality

    analyzeMesh(irregularMesh);
    exportToVTK("output.vtk", irregularMesh);

    return 0;
}

