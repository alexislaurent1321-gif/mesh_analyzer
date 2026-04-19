#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"


std::unordered_map<Edge, size_t, EdgeHash> getEdgeValences(const Mesh<Triangle>& mesh) {
    std::unordered_map<Edge, size_t, EdgeHash> counts;     // Use an unordered_map to count occurrences of each edge
    
    for (const auto& t : mesh.elements) {
        for (size_t i = 0; i < 3; ++i) {
            size_t v1 = t.v[i];
            size_t v2 = t.v[(i + 1) % 3];

            Edge e = {std::min(v1, v2), std::max(v1, v2)};  // Store edges in a consistent order
            counts[e]++;
        }
    }
    
    return counts;
}


std::vector<Edge> getBoundaryEdges(const Mesh<Triangle>& mesh) {
    auto edgeCounts = getEdgeValences(mesh);    // Get the valence counts for all edges
    std::vector<Edge> boundaryEdges;            // Collect edges that belong to only one triangle (valence = 1)
    
    for (auto const& [edge, count] : edgeCounts) {
        if (count == 1) boundaryEdges.push_back(edge);
    }
    
    return boundaryEdges;
}


std::unordered_map<Triangle, size_t, TriangleHash> getTriangleValences(const Mesh<Tetrahedron>& mesh) {
    std::unordered_map<Triangle, size_t, TriangleHash> counts;     // Use an unordered_map to count occurrences of each triangle
    
    for (const auto& t : mesh.elements) {
        for (size_t i = 0; i < 4; ++i) {
            size_t v1 = t.v[i];
            size_t v2 = t.v[(i + 1) % 4];
            size_t v3 = t.v[(i + 2) % 4];

            Triangle triangle = {{std::min({v1, v2, v3}), std::min({std::max(v1, v2), std::max(v2, v3), std::max(v3, v1)}), std::max({v1, v2, v3})}};  // Store triangles in a consistent order
            counts[triangle]++;
        }
    }  
    
    return counts;
}


std::vector<Triangle> getBoundaryTriangles(const Mesh<Tetrahedron>& mesh) {
    auto triangleCounts = getTriangleValences(mesh);    // Get the valence counts for all triangles
    std::vector<Triangle> boundaryTriangles;            // Collect triangles that belong to only one tetrahedron (valence = 1)
    
    for (auto const& [triangle, count] : triangleCounts) {
        if (count == 1) boundaryTriangles.push_back(triangle);
    }
    
    return boundaryTriangles;
}