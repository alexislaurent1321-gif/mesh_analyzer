#include <vector>
#include <fstream>
#include "mesh.h"

/**
 * @brief Export the mesh data to a VTK file format for visualization in tools like ParaView. The function writes the vertices and triangle connectivity to the file, allowing for visualization of the mesh structure and quality.
 * 
 * @param filename 
 * @param mesh 
 */
void exportToVTK(const std::string& filename, const Mesh& mesh) {

    std::ofstream file(filename);
    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Quality Export\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& v : mesh.vertices) 
        file << v.x << " " << v.y << " " << v.z << "\n";

    file << "CELLS " << mesh.triangles.size() << " " << mesh.triangles.size() * 4 << "\n";
    for (const auto& t : mesh.triangles)
        file << "3 " << t.v[0] << " " << t.v[1] << " " << t.v[2] << "\n";

    file << "CELL_TYPES " << mesh.triangles.size() << "\n";
    for (size_t i = 0; i < mesh.triangles.size(); ++i) file << "5\n"; // 5 = Triangle
}