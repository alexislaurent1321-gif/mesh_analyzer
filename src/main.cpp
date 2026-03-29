#include <iostream>

#include "mesh.h"

// Main function to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality
int main() {
    Mesh mesh;

    if (!mesh.loadObj("models/icoSphere1.obj", mesh)) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }

    mesh.analyzeMesh();
    
    return 0;
}

