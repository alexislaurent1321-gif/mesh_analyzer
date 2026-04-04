#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>


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
            return std::hash<int>{}(e.v1) ^ (std::hash<int>{}(e.v2) << 1); // Combine hashes of v1 and v2
        }
    };


    /**
     * @brief Count the number of unique edges in the mesh by iterating through all triangles and adding their edges to an unordered_set
     * 
     * @return number of unique edges in the mesh 
     */
    size_t countUniqueEdges() const;


    // Geometry

    /**
     * @brief   Calculate the aspect ratio of a triangle defined by its vertex indices. An aspect ratio near to 1 indicates a more equilateral triangle
     * 
     * @param t 
     * @return float 
     */
    float calculateAspectRatio(const Triangle& t) const;


    /**
     * @brief  Calculate the aspect ratio for all triangles in the mesh and store them in the ratios vector
     * 
     */
    void calculateAspectRatios();
    

    /**
     * @brief  Analyze the mesh by printing out the number of vertices, triangles, and unique edges. Optionally, it could also calculate and print the aspect ratio of each triangle for quality analysis.
     * 
     */
    void analyzeMesh();


    /**
     * @brief  Load a mesh from an OBJ file using tinyobjloader
     * 
     * @param path Path to the OBJ file to load 
     * @return true 
     * @return false 
     */
    bool loadObj(const std::string& path);


    /**
     * @brief Get the Edge Valences object  
     * 
     * @return std::unordered_map<Mesh::Edge, int, Mesh::EdgeHash> 
     */
    std::unordered_map<Mesh::Edge, int, Mesh::EdgeHash> getEdgeValences() const;


    /** 
     * @brief Get the boundary edges of the mesh
     * @return A vector containing the boundary edges
     */
    std::vector<Edge> getBoundaryEdges() const;

    /** 
     * @brief Smooth the mesh by iteratively moving each vertex towards the centroid of its neighbors
     * @param iterations Number of smoothing iterations to perform
     * @param lambda Smoothing parameter (0 < lambda < 1)
     */
    void smooth(int iterations, float lambda);


    
};

#endif
