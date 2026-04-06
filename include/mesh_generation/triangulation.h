#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <algorithm>
#include <iostream>
#include <string_view>
 
#include "geometry/mesh.h"
#include "mesh_generation/basic_shapes.h"


/** 
 * @brief Class for performing Delaunay triangulation
 */
class Delaunay {

public:
    Mesh mesh;


    /** 
     * @brief Check if a point is inside the circumcircle of a triangle
     * @param A First vertex of the triangle
     * @param B Second vertex of the triangle
     * @param C Third vertex of the triangle
     * @param P The point to check
     * @return true if P is inside the circumcircle, false otherwise
     */
    bool isPointInCircumcircle(const Triangle& triangle, const Point& P);


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