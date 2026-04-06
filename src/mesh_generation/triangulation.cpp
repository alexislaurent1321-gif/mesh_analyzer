#include "mesh_generation/triangulation.h"


Triangle Delaunay::createSuperTriangle() {
    // Create a super-triangle that encompasses all vertices in the mesh
    float minX, minY = std::numeric_limits<float>::max();
    float maxX, maxY = std::numeric_limits<float>::lowest();


    for (const auto& vertex : mesh.vertices) {
        minX = std::min(minX, vertex.x);
        minY = std::min(minY, vertex.y);
        maxX = std::max(maxX, vertex.x);
        maxY = std::max(maxY, vertex.y);
    }

    float dx = maxX - minX;
    float dy = maxY - minY;
    float deltaMax = std::max(dx, dy) * 10; // Scale factor to ensure the super-triangle is large enough

    Point p1 = {minX - deltaMax, minY - deltaMax};
    Point p2 = {minX + dx / 2, maxY + deltaMax};
    Point p3 = {maxX + deltaMax, minY - deltaMax};

    int index1 = mesh.vertices.size();
    int index2 = mesh.vertices.size() + 1;
    int index3 = mesh.vertices.size() + 2;

    mesh.vertices.push_back(p1);
    mesh.vertices.push_back(p2);
    mesh.vertices.push_back(p3);

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
    for (const auto& triangle : badTriangles) {
        Edge edges[3] = {{triangle.v[0], triangle.v[1]}, {triangle.v[1], triangle.v[2]}, {triangle.v[2], triangle.v[0]}};
        for (auto& edge : edges) {
            bool shared = false;
            for (const auto& other : badTriangles) {
                if (&triangle == &other) continue;
                if (other.containsEdge(edge.v1, edge.v2)) {
                    shared = true;
                    break;
                }
            }
            if (!shared) polygon.push_back(edge);
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
    mesh.triangles.erase(std::remove_if(mesh.triangles.begin(), mesh.triangles.end(), 
        [=](const Triangle& triangle) {
            return (triangle.v[0] == superTriangle.v[0] || triangle.v[0] == superTriangle.v[1] || triangle.v[0] == superTriangle.v[2] ||
                    triangle.v[1] == superTriangle.v[0] || triangle.v[1] == superTriangle.v[1] || triangle.v[1] == superTriangle.v[2] ||
                    triangle.v[2] == superTriangle.v[0] || triangle.v[2] == superTriangle.v[1] || triangle.v[2] == superTriangle.v[2]);
        }), mesh.triangles.end());
}


std::vector<Triangle> Delaunay::triangulate() {
    // Start with a super-triangle that encompasses all vertices
    Triangle superTriangle = createSuperTriangle();
    mesh.triangles.push_back(superTriangle);

    // Add each vertex to the triangulation
    for (const auto& vertex : mesh.vertices) {
        addPoint(vertex);
    }

    // Remove triangles that include the vertices of the super-triangle
    cleanup(superTriangle);

    return mesh.triangles;
}