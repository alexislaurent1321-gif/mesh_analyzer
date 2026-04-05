#include "mesh_generation/basic_shapes.h"

void generateGrid(Mesh& mesh, int Nx, int Ny, float Lx, float Ly) {
    float dx = Lx / (Nx - 1);
    float dy = Ly / (Ny - 1);

    for (int j = 0; j < Ny; ++j) {
        for (int i = 0; i < Nx; ++i) {
            mesh.vertices.push_back({i * dx, j * dy});
        }
    }
}