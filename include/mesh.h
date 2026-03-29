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

/**
 * @brief A struct representing a triangle in the mesh
 * 
 */
struct Triangle {
    std::array<int, 3> v; 
};

/**
 * @brief A class representing a 3D mesh
 * 
 */
class Mesh {
public:
    // Datas
    std::vector<Point> vertices;        ///< List of vertices in the mesh
    std::vector<Triangle> triangles;    ///< List of triangles defined by vertex indices
    std::vector<float> ratios;          ///< aspect ratios of triangles (for quality analysis)

    /**
     * @brief A struct representing an edge in the mesh
     * 
     */
    struct Edge {
        int v1, v2;
        bool operator==(const Edge& other) const {
            return v1 == other.v1 && v2 == other.v2;
        }
    };

    /**
     * @brief A hash function for the Edge struct to allow it to be used in an unordered_set
     * 
     */
    struct EdgeHash {
        size_t operator()(const Edge& e) const {
            return std::hash<int>{}(e.v1) ^ (std::hash<int>{}(e.v2) << 1);
        }
    };

    /**
     * @brief Count the number of unique edges in the mesh by iterating through all triangles and adding their edges to an unordered_set
     * 
     * @return number of unique edges in the mesh 
     */
    size_t countUniqueEdges() const {
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

    // Geometry

    /**
     * @brief   Calculate the aspect ratio of a triangle defined by its vertex indices. An aspect ratio near to 1 indicates a more equilateral triangle
     * 
     * @param t 
     * @return float 
     */
    float calculateAspectRatio(const Triangle& t) const {
        float a = vertices[t.v[0]].distance(vertices[t.v[1]]);
        float b = vertices[t.v[1]].distance(vertices[t.v[2]]);
        float c = vertices[t.v[2]].distance(vertices[t.v[0]]);
        float num = a * b * c;
        float denom = (b+c - a) * (c+a - b) * (a+b - c);
        return num / denom;
    }

    /**
     * @brief  Analyze the mesh by printing out the number of vertices, triangles, and unique edges. Optionally, it could also calculate and print the aspect ratio of each triangle for quality analysis.
     * 
     */
    void analyzeMesh() const {
        std::cout << "Vertices : " << vertices.size() << std::endl;
        std::cout << "Triangles : " << triangles.size() << std::endl;
        std::cout << "Unique edges : " << countUniqueEdges() << std::endl;
        // std::cout << "Aspect ratio : " << calculateAspectRatio() << std::endl;
    }

    /**
     * @brief  Load a mesh from an OBJ file using tinyobjloader
     * 
     * @param path 
     * @param myMesh 
     * @return true 
     * @return false 
     */
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
                Triangle triangle;
                triangle.v[0] = shape.mesh.indices[f].vertex_index;
                triangle.v[1] = shape.mesh.indices[f+1].vertex_index;
                triangle.v[2] = shape.mesh.indices[f+2].vertex_index;
                myMesh.triangles.push_back(triangle);
            }
        }
        return true;
    }
};