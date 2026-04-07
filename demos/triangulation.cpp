#include <iostream>

#include "geometry/mesh.h"
#include "visualization/exportToVTK.h"
#include "mesh_generation/triangulation.h"


// Main function to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality
int main() {
    

    // Triangulation test on a grid (for now, without ParaView) // !!! The project will be structured into demos starting tomorrow

    // Example of generating a grid mesh and exporting it
    Mesh gridMesh;
    generateGrid(gridMesh, 5, 5, 1.f, 1.f);

    Delaunay delaunay;
    delaunay.mesh = gridMesh;
    delaunay.mesh.triangles = delaunay.triangulate();

    delaunay.mesh.analyzeMesh();
    exportToVTK("output.vtk", delaunay.mesh);

    
    return 0;
}

