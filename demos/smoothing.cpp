#include <iostream>

#include "mesh.h"
#include "visualization/exportToVTK.h"
#include "processing/triangulation.h"


/** @file triangulation.cpp
 * @brief A simple demo to generate a grid mesh, perform Delaunay triangulation on it, analyze the resulting mesh, and export it to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    // Triangulation test on a grid

    // Example of generating a grid mesh and exporting it
    Mesh gridMesh;
    generateRandomPoints(gridMesh, 25, 1.f, 1.f);

    Delaunay delaunay;
    delaunay.mesh = gridMesh;
    delaunay.mesh.triangles = delaunay.triangulate();

    delaunay.mesh.smooth(100, 1.f); // Apply smoothing to improve triangle quality

    delaunay.mesh.analyzeMesh();
    exportToVTK("output.vtk", delaunay.mesh);

    
    return 0;
}

