#include <numeric>
#include <algorithm>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "mesh.h"


size_t Mesh::countUniqueEdges() const {
    std::unordered_set<Edge, EdgeHash> uniqueEdges;
    for (const auto& t : triangles) {
        for (int i = 0; i < 3; ++i) {
            int a = t.v[i];
            int b = t.v[(i + 1) % 3];
            uniqueEdges.insert({std::min(a, b), std::max(a, b)});
        }
    }
    return uniqueEdges.size();
}

float Mesh::calculateAspectRatio(const Triangle& t) const {
    float a = vertices[t.v[0]].distance(vertices[t.v[1]]);
    float b = vertices[t.v[1]].distance(vertices[t.v[2]]);
    float c = vertices[t.v[2]].distance(vertices[t.v[0]]);
    float num = a * b * c;
    float denom = (b+c - a) * (c+a - b) * (a+b - c);
    return num / denom;
}

void Mesh::calculateAspectRatios() {
    ratios.clear();
    for (const auto& t : triangles) {
        ratios.push_back(calculateAspectRatio(t));
    }
}

void Mesh::analyzeMesh() {
    std::cout << "Vertices : " << vertices.size() << std::endl;
    std::cout << "Triangles : " << triangles.size() << std::endl;
    std::cout << "Unique edges : " << countUniqueEdges() << std::endl;
    calculateAspectRatios();
    std::cout << "min aspect ratio : " << *std::min_element(ratios.begin(), ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(ratios.begin(), ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(ratios.begin(), ratios.end(), 0.f) / ratios.size() << std::endl;
}

bool Mesh::loadObj(const std::string& path, Mesh& myMesh) {
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config)) return false;

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // Load vertices
    for (size_t v = 0; v < attrib.vertices.size(); v += 3) {
        myMesh.vertices.push_back({
            attrib.vertices[v], 
            attrib.vertices[v + 1], 
            attrib.vertices[v + 2]
        });
    }

    // Load triangles
    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
            int fv = shape.mesh.num_face_vertices[f];
            if (fv != 3) continue; // Only support triangles

            Triangle triangle;
            for (size_t v = 0; v < fv; ++v) {
                triangle.v[v] = shape.mesh.indices[index_offset + v].vertex_index;
            }
            myMesh.triangles.push_back(triangle);
            index_offset += fv;
        }
    }

    return true;
}