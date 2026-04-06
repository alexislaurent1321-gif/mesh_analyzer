#include "mesh_generation/triangulation.h"


Triangle Delaunay::createSuperTriangle() {

    float minX = 1e7f;
    float minY = 1e7f;
    float maxX = -1e7f;
    float maxY = -1e7f;

    // Find the bounding box of the existing vertices
    for (const auto& vertex : mesh.vertices) {
        minX = std::min(minX, vertex.x);
        minY = std::min(minY, vertex.y);
        maxX = std::max(maxX, vertex.x);
        maxY = std::max(maxY, vertex.y);
    }

    float dx = (maxX - minX) * 10; // Scale factor to ensure the super-triangle is large enough
    float dy = (maxY - minY) * 10; // Scale factor to ensure the super-triangle is large enough

    // Define the vertices of the super-triangle
    Point v0 = {minX - dx, minY - dy * 3};
    Point v1 = {minX + dx, maxY + dy};
    Point v2 = {maxX + dx * 3, minY - dy};

    // Store the super-triangle vertices in the mesh and return the triangle defined by their indices
    int index1 = mesh.vertices.size();
    int index2 = mesh.vertices.size() + 1;
    int index3 = mesh.vertices.size() + 2;

    // superTriangleVertices = {v0, v1, v2} // Store the super-triangle vertices for later cleanup
    mesh.vertices.push_back(v0);
    mesh.vertices.push_back(v1);
    mesh.vertices.push_back(v2);

    return {index1, index2, index3};
}


 void Delaunay::addPoint(const Point& point) {

    // Add the new point to the mesh and get its index
    int pointIndex = mesh.vertices.size();
    mesh.vertices.push_back(point);

    // Find all triangles whose circumcircle contains the new point
    std::vector<Triangle> badTriangles;
    for (auto& triangle : mesh.triangles) {
        if (triangle.containsPoint(mesh.vertices, point)) {
            triangle.isBad = true;
            badTriangles.push_back(triangle);
        }
    }

    // Find the boundary of the polygonal hole created by removing the bad triangles
    std::vector<Edge> polygon;
    for (const auto& tri : badTriangles) {
        
        // Check each edge of the triangle to see if it's shared by another bad triangle
        Edge edges[3] = { {tri.v[0], tri.v[1]}, {tri.v[1], tri.v[2]}, {tri.v[2], tri.v[0]} };
        
        // For each edge, check if it's shared by another bad triangle. If not, it's part of the polygon boundary
        for (const auto& edge : edges) {
            bool isShared = false;  // Check if this edge is shared by another bad triangle
            for (const auto& otherTri : badTriangles) {

                if (&tri == &otherTri) continue;

                if (otherTri.containsEdge(edge.v1, edge.v2)) {
                    isShared = true;
                    break;
                }
            }
            if (!isShared) {
                polygon.push_back(edge);
            }
        }
    }

    // Remove the bad triangles from the mesh
    mesh.triangles.erase(std::remove_if(mesh.triangles.begin(), mesh.triangles.end(), 
                    [](const Triangle& triangle){ return triangle.isBad; }), mesh.triangles.end());

    // Retriangulate the polygonal hole by connecting the new point to the vertices of the polygon
    for (const auto& edge : polygon) {
        mesh.triangles.push_back({edge.v1, edge.v2, pointIndex});
    }
}


void Delaunay::cleanup(Triangle superTriangle) {
    // Remove triangles that include the vertices of the super-triangle
    mesh.triangles.erase(std::remove_if(mesh.triangles.begin(), mesh.triangles.end(), 
        [=](const Triangle& triangle) {
            return (triangle.v[0] == superTriangle.v[0] || triangle.v[0] == superTriangle.v[1] || triangle.v[0] == superTriangle.v[2] ||
                    triangle.v[1] == superTriangle.v[0] || triangle.v[1] == superTriangle.v[1] || triangle.v[1] == superTriangle.v[2] ||
                    triangle.v[2] == superTriangle.v[0] || triangle.v[2] == superTriangle.v[1] || triangle.v[2] == superTriangle.v[2]);
        }), mesh.triangles.end());

    // Remove the super-triangle vertices from the mesh
    mesh.vertices.erase(mesh.vertices.end() - 3, mesh.vertices.end());
}


std::vector<Triangle> Delaunay::triangulate() {

    std::vector<Point> tmp_vertices = mesh.vertices; // Store the original vertices before adding the super-triangle vertices

    mesh.vertices.clear(); // Clear the mesh vertices to start fresh with the super-triangle and the original vertices
    mesh.triangles.clear(); // Clear the mesh triangles to start fresh

    // Start with a super-triangle that encompasses all vertices
    Triangle superTriangle = createSuperTriangle();
    mesh.triangles.push_back(superTriangle);

    // Add each vertex to the triangulation
    for (const auto& vertex : tmp_vertices) {
        addPoint(vertex);
    }

    // Remove triangles that include the vertices of the super-triangle
    cleanup(superTriangle);

    return mesh.triangles;
}