#include "io/loadMsh.h"
#include <mshio/mshio.h>
#include <map>


bool loadMsh(Mesh<Triangle>& mesh, const std::string& path) {
    // Create a Mshio object to read the MSH file
    mshio::MshSpec data;
    try {
        data = mshio::load_msh(path);
    } catch (const std::exception& e) {
        std::cerr << "Error reading .msh file : " << e.what() << std::endl;
        return false;
    }

    mesh.vertices.clear();
    mesh.elements.clear();

    std::map<size_t, size_t> node_tag_to_index;

    for (const auto& node_block : data.nodes.entity_blocks) {
        for (size_t i = 0; i < node_block.num_nodes_in_block; ++i) {
            size_t tag = node_block.tags[i];
            node_tag_to_index[tag] = mesh.vertices.size();

            // Add the vertex to the mesh's vertex list
            mesh.vertices.push_back({
                static_cast<float>(node_block.data[i * 3]),     // x
                static_cast<float>(node_block.data[i * 3 + 1]), // y
                static_cast<float>(node_block.data[i * 3 + 2])  // z
            });
        }
    }

    int target_gmsh_type = 0;
    size_t nodes_per_element = 0;   // Gmsh type 2 corresponds to 3-node triangles

    target_gmsh_type = 2;
    nodes_per_element = 3;  

    // Iterate through the element blocks and extract triangular elements
    for (const auto& element_block : data.elements.entity_blocks) {
        // Check if the element block corresponds to the target Gmsh type (e.g., 2 for 3-node triangles)
        if (element_block.element_type == target_gmsh_type) {
            for (size_t i = 0; i < element_block.num_elements_in_block; ++i) {
                Triangle element;
                
                // For each vertex of the element, get the corresponding node tag and convert it to a vertex index
                for (size_t v_idx = 0; v_idx < nodes_per_element; ++v_idx) {
                    size_t node_tag = element_block.data[i * nodes_per_element + v_idx];
                    element.v[v_idx] = node_tag_to_index[node_tag];
                }
                mesh.elements.push_back(element); 
            }
        }
    }

    return !mesh.elements.empty();
}


bool loadMsh(Mesh<Tetrahedron>& mesh, const std::string& path) {
    
    // Create a Mshio object to read the MSH file
    mshio::MshSpec data;
    try {
        data = mshio::load_msh(path);
    } catch (const std::exception& e) {
        std::cerr << "Error reading .msh file : " << e.what() << std::endl;
        return false;
    }

    mesh.vertices.clear();
    mesh.elements.clear();

    std::map<size_t, size_t> node_tag_to_index;

    for (const auto& node_block : data.nodes.entity_blocks) {
        for (size_t i = 0; i < node_block.num_nodes_in_block; ++i) {
            size_t tag = node_block.tags[i];
            node_tag_to_index[tag] = mesh.vertices.size();

            // Add the vertex to the mesh's vertex list
            mesh.vertices.push_back({
                static_cast<float>(node_block.data[i * 3]),     // x
                static_cast<float>(node_block.data[i * 3 + 1]), // y
                static_cast<float>(node_block.data[i * 3 + 2])  // z
            });
        }
    }

    int target_gmsh_type = 0;
    size_t nodes_per_element = 0;   // Gmsh type 4 corresponds to 4-node tetrahedra

    target_gmsh_type = 4;
    nodes_per_element = 4;

    // Iterate through the element blocks and extract tetrahedral elements
    for (const auto& element_block : data.elements.entity_blocks) {

        // Check if the element block corresponds to the target Gmsh type (e.g., 4 for 4-node tetrahedra)
        if (element_block.element_type == target_gmsh_type) {
            for (size_t i = 0; i < element_block.num_elements_in_block; ++i) {
                Tetrahedron element;
                
                // For each vertex of the element, get the corresponding node tag and convert it to a vertex index
                for (size_t v_idx = 0; v_idx < nodes_per_element; ++v_idx) {
                    size_t node_tag = element_block.data[i * nodes_per_element + v_idx];
                    element.v[v_idx] = node_tag_to_index[node_tag];
                }
                mesh.elements.push_back(element); 
            }
        }
    }

    return !mesh.elements.empty();
}

  