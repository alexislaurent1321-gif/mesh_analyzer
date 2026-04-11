#include "smoothing.h"


void smooth(Mesh& mesh, int iterations, float lambda){
        
    // Build an adjacency list for the vertices based on the triangles
    std::unordered_map<int, std::unordered_set<int>> adjacency; 
    std::unordered_set<int> boundaryVertices; // Keep track of boundary vertices to avoid moving them during smoothing

    // Get boundary vertices from boundary edges
    std::vector<Edge> boundaryEdges = getBoundaryEdges(mesh);
    for (const auto& edge : boundaryEdges) {
        boundaryVertices.insert(edge.v1);
        boundaryVertices.insert(edge.v2);
    }

    // Build the adjacency list
    for (const auto& triangle : mesh.triangles) {
        adjacency[triangle.v[0]].insert({triangle.v[1], triangle.v[2]});
        adjacency[triangle.v[1]].insert({triangle.v[0], triangle.v[2]});
        adjacency[triangle.v[2]].insert({triangle.v[0], triangle.v[1]});
    }

    // Perform smoothing iterations
    for(int iter = 0; iter < iterations; ++iter) {
        std::vector<Point> nextPositions = mesh.vertices;
        for (int i = 0; i < mesh.vertices.size(); ++i) {

            if (boundaryVertices.count(i)) {
                continue; 
            }

            if (adjacency[i].empty()) continue;

            Point centroid = {0, 0, 0};
            for (int neighborIdx : adjacency[i]) {
                centroid += mesh.vertices[neighborIdx];
            }
            centroid /= adjacency[i].size();
            
            // Update the vertex position by moving it towards the centroid of its neighbors
            nextPositions[i] = mesh.vertices[i] + (centroid - mesh.vertices[i]) * lambda;
        }

        mesh.vertices = nextPositions; // Update the vertex positions after smoothing
    }
}