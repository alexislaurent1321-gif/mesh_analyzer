#include <iostream>

#include "mesh.h"
#include "exportToVTK.h"

// Main function to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality
int main() {
    Mesh mesh;

    if (!mesh.loadObj("models/icoSphere2.obj", mesh)) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }

    mesh.analyzeMesh();

    exportToVTK("output.vtk", mesh);    
    
    return 0;
}

