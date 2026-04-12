#include <numeric>
#include <algorithm>
#define TINYOBJLOADER_IMPLEMENTATION
#include <extern/tiny_obj_loader.h>

#include "io/loadObj.h"

bool loadObj(Mesh<Triangle>& mesh, const std::string& path) {
    tinyobj::ObjReaderConfig reader_config; // Create a reader configuration object (optional)
    tinyobj::ObjReader reader;              // Create an ObjReader object to read the OBJ file

    if (!reader.ParseFromFile(path, reader_config)) return false;

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // Load vertices
    for (size_t v = 0; v < attrib.vertices.size(); v += 3) {
        mesh.vertices.push_back({
            attrib.vertices[v], 
            attrib.vertices[v + 1], 
            attrib.vertices[v + 2]
        });
    }

    
    // Load triangles
    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
            int fv = shape.mesh.num_face_vertices[f];   // Get the number of vertices for this face
            if (fv != 3) continue;                      // Only support triangles

            // Create a Triangle object and fill its vertex indices
            Triangle triangle;
            for (size_t v = 0; v < fv; ++v) {
                triangle.v[v] = shape.mesh.indices[index_offset + v].vertex_index;
            }
            mesh.elements.push_back(triangle);

            index_offset += fv; // Move to the next face
        }
    }

    return true;
}