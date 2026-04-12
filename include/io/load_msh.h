#include "mesh/mesh.h"

/**
 * @brief   Load a tetrahedral mesh from a .msh file in Gmsh format
 * 
 * @param mesh 
 * @param path 
 * @return true 
 * @return false 
 */
bool load_msh(Mesh<Tetrahedron>& mesh, const std::string& path);