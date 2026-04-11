#include "visualization/exportToVTK.h"
#include "analysis.h"

void exportToVTK(const std::string& filename, const Mesh& mesh) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    // Identify boundary edges (edges that belong to only one triangle)
    std::vector<Edge> boundaryEdges = getBoundaryEdges(mesh);

    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Analysis Combo\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    // Write vertices
    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& v : mesh.vertices) 
        file << v.x << " " << v.y << " " << v.z << "\n";

    // Write cells (triangles + boundary edges)
    size_t nT = mesh.triangles.size();
    size_t nB = boundaryEdges.size();
    file << "CELLS " << (nT + nB) << " " << (nT * 4 + nB * 3) << "\n";
    
    for (const auto& t : mesh.triangles)
        file << "3 " << t.v[0] << " " << t.v[1] << " " << t.v[2] << "\n";
    for (const auto& e : boundaryEdges)
        file << "2 " << e.v1 << " " << e.v2 << "\n";

    file << "CELL_TYPES " << (nT + nB) << "\n";
    for (size_t i = 0; i < nT; ++i) file << "5\n"; // Triangles
    for (size_t i = 0; i < nB; ++i) file << "3\n"; // Lines


    // Write cell data (quality ratios and boundary flags)
    file << "CELL_DATA " << (nT + nB) << "\n";


    file << "SCALARS Quality_Ratio float\nLOOKUP_TABLE default\n";
    for (float r : mesh.ratios) file << r << "\n";
    for (size_t i = 0; i < nB; ++i) file << "0.\n"; 


    // Boundary representation: 0 for triangles, 1 for boundary edges 
    file << "SCALARS Is_Boundary int\nLOOKUP_TABLE default\n";
    for (size_t i = 0; i < nT; ++i) file << "0\n"; // Triangle = 0
    for (size_t i = 0; i < nB; ++i) file << "1\n"; // Boundary = 1

    file.close();
}