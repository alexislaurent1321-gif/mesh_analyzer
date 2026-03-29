#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "point.h"


// Face : vertices indices (triangles)
struct Face {
    std::array<int, 3> v; 
};

class Mesh {
public:
    // Datas
    std::vector<Point> vertices;
    std::vector<Face> faces;
    
    // Edge defined by two vertex indices (v1, v2)
    struct Edge {
        int v1, v2;
        bool operator==(const Edge& other) const {
            return v1 == other.v1 && v2 == other.v2;
        }
    };

    // Hash function for Edge to be used in unordered_set
    struct EdgeHash {
        size_t operator()(const Edge& e) const {
            return std::hash<int>{}(e.v1) ^ (std::hash<int>{}(e.v2) << 1);
        }
    };

    // count unique edges in the mesh
    size_t countUniqueEdges() const {
        std::unordered_set<Edge, EdgeHash> uniqueEdges;
        for (const auto& f : faces) {
            for (int i = 0; i < 3; ++i) {
                int a = f.v[i];
                int b = f.v[(i + 1) % 3];
                uniqueEdges.insert({std::min(a, b), std::max(a, b)});
            }
        }
        return uniqueEdges.size();
    }

    // Geometry

    // Calculate aspect ratio of a face (we expect it to be close to 1 for equilateral triangles)
    float calculateAspectRatio(const Face& f) const {
        float a = vertices[f.v[0]].distance(vertices[f.v[1]]);
        float b = vertices[f.v[1]].distance(vertices[f.v[2]]);
        float c = vertices[f.v[2]].distance(vertices[f.v[0]]);
        float num = a * b * c;
        float denom = (b+c - a) * (c+a - b) * (a+b - c);
        return num / denom;
    }

    // Analyze mesh quality and print basic stats
    void analyzeMesh() const {
        std::cout << "Vertices : " << vertices.size() << std::endl;
        std::cout << "Faces : " << faces.size() << std::endl;
        std::cout << "Unique edges : " << countUniqueEdges() << std::endl;
        // std::cout << "Aspect ratio : " << calculateAspectRatio() << std::endl;
    }

    // Load mesh from OBJ file using tinyobjloader
    bool loadObj(const std::string& path, Mesh& myMesh) {
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

        // Load faces (triangles)
        for (const auto& shape : shapes) {
            for (size_t f = 0; f < shape.mesh.indices.size(); f += 3) {
                Face face;
                face.v[0] = shape.mesh.indices[f].vertex_index;
                face.v[1] = shape.mesh.indices[f+1].vertex_index;
                face.v[2] = shape.mesh.indices[f+2].vertex_index;
                myMesh.faces.push_back(face);
            }
        }
        return true;
    }
};