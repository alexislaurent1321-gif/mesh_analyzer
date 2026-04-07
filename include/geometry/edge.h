#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>


#include "geometry/point.h"

/**
 * @brief A struct representing an edge in the mesh
 * 
 */
struct Edge {
    int v1, v2;
    bool operator==(const Edge& other) const {
        return (v1 == other.v1 && v2 == other.v2) || (v1 == other.v2 && v2 == other.v1);
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

#endif  