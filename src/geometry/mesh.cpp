#include <numeric>
#include <algorithm>
#define TINYOBJLOADER_IMPLEMENTATION
#include <extern/tiny_obj_loader.h>

#include "geometry/mesh.h"


size_t Mesh::countUniqueEdges() const {
    std::unordered_set<Edge, EdgeHash> uniqueEdges; // Use an unordered_set to store unique edges
    
    // Iterate through all triangles and add their edges to the set
    for (const auto& t : triangles) {
        for (int i = 0; i < 3; ++i) {
            int v1 = t.v[i];
            int v2 = t.v[(i + 1) % 3];

            // Store edges in a consistent order to avoid duplicates
            uniqueEdges.insert({std::min(v1, v2), std::max(v1, v2)}); 
        }
    }
    return uniqueEdges.size();
}


float Mesh::calculateAspectRatio(const Triangle& t) const {
    // triangle lengths
    float a = vertices[t.v[0]].distance(vertices[t.v[1]]);
    float b = vertices[t.v[1]].distance(vertices[t.v[2]]);
    float c = vertices[t.v[2]].distance(vertices[t.v[0]]);

    // aspect ratio formula: (abc) / ((b+c-a)(c+a-b)(a+b-c))
    float num = a * b * c;
    float denom = (b+c - a) * (c+a - b) * (a+b - c);
    return num / denom;
}


void Mesh::calculateAspectRatios() {
    ratios.clear();

    // Calculate aspect ratio for each triangle and store in the ratios vector
    for (const auto& t : triangles) {
        ratios.push_back(calculateAspectRatio(t));
    }
}


void Mesh::analyzeMesh() {
    // Basic info
    std::cout << "Vertices : " << vertices.size() << std::endl;
    std::cout << "Triangles : " << triangles.size() << std::endl;
    std::cout << "Unique edges : " << countUniqueEdges() << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios();
    std::cout << "min aspect ratio : " << *std::min_element(ratios.begin(), ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(ratios.begin(), ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(ratios.begin(), ratios.end(), 0.f) / ratios.size() << std::endl;
}


bool Mesh::loadObj(const std::string& path) {
    tinyobj::ObjReaderConfig reader_config; // Create a reader configuration object (optional)
    tinyobj::ObjReader reader;              // Create an ObjReader object to read the OBJ file

    if (!reader.ParseFromFile(path, reader_config)) return false;

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // Load vertices
    for (size_t v = 0; v < attrib.vertices.size(); v += 3) {
        vertices.push_back({
            attrib.vertices[v], 
            attrib.vertices[v + 1], 
            attrib.vertices[v + 2]
        });
    }

    
    // Load triangles
    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
            int fv = shape.mesh.num_face_vertices[f];   // Get the number of vertices for this face
            if (fv != 3) continue;                      // Only support triangles

            // Create a Triangle object and fill its vertex indices
            Triangle triangle;
            for (size_t v = 0; v < fv; ++v) {
                triangle.v[v] = shape.mesh.indices[index_offset + v].vertex_index;
            }
            triangles.push_back(triangle);

            index_offset += fv; // Move to the next face
        }
    }

    return true;
}


std::unordered_map<Edge, int, EdgeHash> Mesh::getEdgeValences() const {
    std::unordered_map<Edge, int, EdgeHash> counts;     // Use an unordered_map to count occurrences of each edge
    
    for (const auto& t : triangles) {
        for (int i = 0; i < 3; ++i) {
            int v1 = t.v[i];
            int v2 = t.v[(i + 1) % 3];

            Edge e = {std::min(v1, v2), std::max(v1, v2)};  // Store edges in a consistent order
            counts[e]++;
        }
    }
    
    return counts;
}


std::vector<Edge> Mesh::getBoundaryEdges() const {
    auto edgeCounts = getEdgeValences();    // Get the valence counts for all edges
    std::vector<Edge> boundaryEdges;        // Collect edges that belong to only one triangle (valence = 1)
    
    for (auto const& [edge, count] : edgeCounts) {
        if (count == 1) boundaryEdges.push_back(edge);
    }
    
    return boundaryEdges;
}


void Mesh::smooth(int iterations, float lambda){
        
    // Build an adjacency list for the vertices based on the triangles
    std::unordered_map<int, std::unordered_set<int>> adjacency; 
    std::unordered_set<int> boundaryVertices; // Keep track of boundary vertices to avoid moving them during smoothing

    // Get boundary vertices from boundary edges
    std::vector<Edge> boundaryEdges = getBoundaryEdges();
    for (const auto& edge : boundaryEdges) {
        boundaryVertices.insert(edge.v1);
        boundaryVertices.insert(edge.v2);
    }

    for (const auto& triangle : triangles) {
        adjacency[triangle.v[0]].insert({triangle.v[1], triangle.v[2]});
        adjacency[triangle.v[1]].insert({triangle.v[0], triangle.v[2]});
        adjacency[triangle.v[2]].insert({triangle.v[0], triangle.v[1]});
    }

    // Perform smoothing iterations
    for(int iter = 0; iter < iterations; ++iter) {
        std::vector<Point> nextPositions = vertices;
        for (int i = 0; i < vertices.size(); ++i) {

            if (boundaryVertices.count(i)) {
                continue; 
            }

            if (adjacency[i].empty()) continue;

            Point centroid = {0, 0, 0};
            for (int neighborIdx : adjacency[i]) {
                centroid += vertices[neighborIdx];
            }
            centroid /= adjacency[i].size();
            
            // Update the vertex position by moving it towards the centroid of its neighbors
            nextPositions[i] = vertices[i] + (centroid - vertices[i]) * lambda;
        }

        vertices = nextPositions; // Update the vertex positions after smoothing
    }
}