#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>

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
    
    // Edge definedd by two vertex indices (v1, v2)
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
        //  a*b*c / ( (b+c-a)*(c+a-b)*(a+b-c) )
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
    }

    // Load mesh from OBJ file (only vertices and faces)
    bool loadOBJ(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return false;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type;
            ss >> type;

            if (type == "v") { // vertex
                Point v;
                ss >> v.x >> v.y >> v.z;
                vertices.push_back(v);
            } else if (type == "f") { // face
                Face f;
                for (int i = 0; i < 3; ++i) {
                    std::string segment;
                    ss >> segment;
                   
                    f.v[i] = std::stoi(segment.substr(0, segment.find('/'))) - 1;
                }
                faces.push_back(f);
            }
        }
        return true;
    }
};