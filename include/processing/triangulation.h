#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <algorithm>
#include <iostream>
#include <string_view>
 
#include "mesh.h"
#include "processing/basic_shapes.h"


/** 
 * @brief Class for performing Delaunay triangulation
 */
class Delaunay {

public:
    Mesh mesh;

    
    /** 
     * @brief Create a super-triangle that encompasses all vertices in the mesh
     * @return The super-triangle
     */
    Triangle createSuperTriangle();


    /** 
     * @brief Add a point to the triangulation and update the mesh accordingly
     * @param point The point to add
     */
    void addPoint(const Point& point);


    /** 
     * @brief Clean up the mesh by removing triangles that include the vertices of the super-triangle
     * @param superTriangle The super-triangle
     */
    void cleanup(Triangle superTriangle);


    /** 
     * @brief Perform Delaunay triangulation on the current set of vertices in the mesh
     * @return A vector of triangles representing the Delaunay triangulation
     */
    std::vector<Triangle> triangulate();
   
};

#endif  