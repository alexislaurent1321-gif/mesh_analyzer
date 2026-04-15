#ifndef LOAD_MSH_H
#define LOAD_MSH_H

#include "mesh/mesh.h"


/**
 * @brief   Load a triangular mesh from a .msh file in Gmsh format
 * 
 * @param mesh 
 * @param path 
 * @return true 
 * @return false 
 */
bool loadMsh(Mesh<Triangle>& mesh, const std::string& path);


/**
 * @brief   Load a tetrahedral mesh from a .msh file in Gmsh format
 * 
 * @param mesh 
 * @param path 
 * @return true 
 * @return false 
 */
bool loadMsh(Mesh<Tetrahedron>& mesh, const std::string& path);

#endif 