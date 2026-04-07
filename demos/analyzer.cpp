#include <iostream>

#include "geometry/mesh.h"
#include "visualization/exportToVTK.h"
#include "mesh_generation/triangulation.h"


/** @file analyzer.cpp
 * @brief A simple demo to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality. It also exports the mesh to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    Mesh mesh;

    if (!mesh.loadObj("models/demi_sphere_broken.obj")) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }
    
    mesh.analyzeMesh();

    std::cout << "Exporting mesh to VTK format..." << std::endl;
    exportToVTK("output.vtk", mesh);
    
    return 0;
}

