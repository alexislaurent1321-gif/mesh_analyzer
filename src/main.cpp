#include <iostream>

#include "mesh.h"

int main() {
    Mesh mesh;

    if (!mesh.loadObj("models/icoSphere1.obj", mesh)) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }

    mesh.analyzeMesh();
    
    return 0;
}

