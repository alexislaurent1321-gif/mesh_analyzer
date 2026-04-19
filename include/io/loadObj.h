#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include "mesh/mesh.h"

/**
 * @brief  Load a triangular mesh from an OBJ file using tinyobjloader
 * 
 * @param path Path to the OBJ file to load 
 * @return true 
 * @return false 
 */
bool loadObj(Mesh<Triangle>& mesh, const std::string& path);

#endif

