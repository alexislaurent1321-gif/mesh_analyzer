#include <iostream>

// #include "load.h"
// #include "mesh.h"

// int main() {
//     Mesh mesh;
//     if (!loadOBJ("model.obj")) {
//         std::cerr << "Error loading OBJ file." << std::endl;
//         return 1;
//     }
//     mesh.analyzeMesh();
//     return 0;
// }

#include "point.h"

int main() {
    Point p1(1, 2, 3);
    Point p2(4, 5, 6);
    std::cout << "Point 1: " << p1 << std::endl;
    std::cout << "Point 2: " << p2 << std::endl;
    std::cout << "Distance: " << p1.distance(p2) << std::endl;
    return 0;
}
