#include "mesh/mesh.h"

/**
 * @brief  Load a mesh from an OBJ file using tinyobjloader
 * 
 * @param path Path to the OBJ file to load 
 * @return true 
 * @return false 
 */
bool loadObj(Mesh& mesh, const std::string& path);
