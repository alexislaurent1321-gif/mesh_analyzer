#include "mesh.h"

/** 
 * @brief Exports the mesh data to a VTK file for visualization in Paraview
 * @param filename The name of the output VTK file
 * @param mesh The mesh object containing vertices, triangles, and quality ratios
*/
void exportToVTK(const std::string& filename, const Mesh& mesh);