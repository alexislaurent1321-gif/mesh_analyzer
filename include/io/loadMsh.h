#ifndef LOAD_MSH_H
#define LOAD_MSH_H

#include "mesh/mesh.h"


/**
 * @brief   Load a mesh from a .msh file in Gmsh format
 * 
 * @param mesh 
 * @param path 
 * @return true 
 * @return false 
 */
template <typename T>
bool loadMsh(Mesh<T>& mesh, const std::string& path);

#include "../src/io/loadMsh.tpp"

#endif 