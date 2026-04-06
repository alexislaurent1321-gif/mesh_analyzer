#include <iostream>

#include "geometry/mesh.h"
#include "visualization/exportToVTK.h"
#include "mesh_generation/triangulation.h"


// Main function to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality
int main() {
    

    // Mesh Analyzer

    Mesh mesh;

    if (!mesh.loadObj("models/cube_high_res.obj")) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }

    mesh.smooth(10, 1.f);   // Optional: Smooth 
    
    mesh.analyzeMesh();

    std::cout << "Exporting mesh to VTK format..." << std::endl;
    exportToVTK("output.vtk", mesh);

    

    // Triangulation test on a grid (for now, without ParaView)

    // // Example of generating a grid mesh and exporting it
    // Mesh gridMesh;
    // generateGrid(gridMesh, 5, 5, 1.f, 1.f);

    // Delaunay delaunay;
    // delaunay.mesh = gridMesh;
    // delaunay.mesh.triangles = delaunay.triangulate();

    // delaunay.mesh.analyzeMesh();
    // exportToVTK("output.vtk", delaunay.mesh);

    
    return 0;
}

