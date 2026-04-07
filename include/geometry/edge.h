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
    int u, v;
    bool operator==(const Edge& other) const {
        return u == other.u && v == other.v;
    }
};

 /**
 * @brief A hash function for the Edge struct to allow it to be used in an unordered_set
 * 
 */
struct EdgeHash {
    size_t operator()(const Edge& e) const {
        return std::hash<int>{}(e.u) ^ (std::hash<int>{}(e.v) << 1); // Combine hashes of u and v
    }
};

#endif  