#include <iostream>

#include "geometry/mesh.h"
#include "visualization/exportToVTK.h"
#include "mesh_generation/triangulation.h"


/** @file smoothing.cpp
 * @brief A simple demo to load a mesh from an OBJ file, apply Laplacian smoothing to improve the mesh quality, and print out basic statistics about the mesh. It also exports the smoothed mesh to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    Mesh mesh;

    if (!mesh.loadObj("models/cube_high_res.obj")) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }

    mesh.smooth(10, 1.f);   // Optional: Smooth 
    
    mesh.analyzeMesh();

    std::cout << "Exporting mesh to VTK format..." << std::endl;
    exportToVTK("output.vtk", mesh);
    
    return 0;
}

