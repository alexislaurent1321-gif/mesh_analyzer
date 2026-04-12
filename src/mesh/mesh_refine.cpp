#include "mesh/mesh_refine.h"

void refine(Mesh<Triangle>& mesh, int iterations){
    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<Triangle> newTriangles;

        for (const auto& triangle : mesh.elements) {

            if(calculateAspectRatio(mesh, triangle) < 2.f) {
                continue; // Skip refinement for this triangle
            }

            // Get the vertices of the triangle
            Point v0 = mesh.vertices[triangle.v[0]];
            Point v1 = mesh.vertices[triangle.v[1]];
            Point v2 = mesh.vertices[triangle.v[2]];

            // Calculate the midpoints of each edge
            Point m01 = (v0 + v1) / 2.f;
            Point m12 = (v1 + v2) / 2.f;
            Point m20 = (v2 + v0) / 2.f;

            // Add the midpoints to the vertex list and get their indices
            int m01Index = mesh.vertices.size();
            int m12Index = mesh.vertices.size() + 1;
            int m20Index = mesh.vertices.size() + 2;

            mesh.vertices.push_back(m01);
            mesh.vertices.push_back(m12);
            mesh.vertices.push_back(m20);

            // Create new triangles by connecting the midpoints
            newTriangles.push_back({triangle.v[0], m01Index, m20Index});
            newTriangles.push_back({triangle.v[1], m12Index, m01Index});
            newTriangles.push_back({triangle.v[2], m20Index, m12Index});
            newTriangles.push_back({m01Index, m12Index, m20Index});
        }

        for(const auto& triangle : newTriangles) {
            mesh.elements.push_back(triangle);
        }
    }
}