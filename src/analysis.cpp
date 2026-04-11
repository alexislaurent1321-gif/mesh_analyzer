#include <numeric>

#include "analysis.h"

size_t countUniqueEdges(const Mesh& mesh) {
    std::unordered_set<Edge, EdgeHash> uniqueEdges; // Use an unordered_set to store unique edges
    
    // Iterate through all triangles and add their edges to the set
    for (const auto& t : mesh.triangles) {
        for (int i = 0; i < 3; ++i) {
            int v1 = t.v[i];
            int v2 = t.v[(i + 1) % 3];

            // Store edges in a consistent order to avoid duplicates
            uniqueEdges.insert({std::min(v1, v2), std::max(v1, v2)}); 
        }
    }
    return uniqueEdges.size();
}


float calculateAspectRatio(const Mesh& mesh, const Triangle& t)  {
    // triangle lengths
    float a = mesh.vertices[t.v[0]].distance(mesh.vertices[t.v[1]]);
    float b = mesh.vertices[t.v[1]].distance(mesh.vertices[t.v[2]]);
    float c = mesh.vertices[t.v[2]].distance(mesh.vertices[t.v[0]]);

    // aspect ratio formula: (abc) / ((b+c-a)(c+a-b)(a+b-c))
    float num = a * b * c;
    float denom = (b+c - a) * (c+a - b) * (a+b - c);
    return num / denom;
}


void calculateAspectRatios(Mesh& mesh) {
    mesh.ratios.clear();

    // Calculate aspect ratio for each triangle and store in the ratios vector
    for (const auto& t : mesh.triangles) {
        mesh.ratios.push_back(calculateAspectRatio(mesh, t));
    }
}


void analyzeMesh(Mesh& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Triangles : " << mesh.triangles.size() << std::endl;
    std::cout << "Unique edges : " << countUniqueEdges(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}