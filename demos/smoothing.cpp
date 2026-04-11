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
    Mesh irregularMesh;
    generateRandomPoints(irregularMesh, 25, 1.f, 1.f);

    triangulate(irregularMesh); // Perform Delaunay triangulation on the grid mesh

    smooth(irregularMesh, 100, 1.f); // Apply smoothing to improve triangle quality

    // refine(irregularMesh, 2); // Refine the mesh to further improve quality

    analyzeMesh(irregularMesh);
    exportToVTK("output.vtk", irregularMesh);

    return 0;
}

