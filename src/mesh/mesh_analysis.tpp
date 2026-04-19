#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"


// Quality analysis

template <typename T>
size_t countUniqueEdges(const Mesh<T>& mesh) {
    std::unordered_set<Edge, EdgeHash> uniqueEdges; // Use an unordered_set to store unique edges
    
    std::cout << "numVertices : " << T::numVertices << std::endl;
    // Iterate through all triangles and add their edges to the set
    for (const auto& t : mesh.elements) {
        for (size_t i = 0; i < T::numVertices; ++i) {
            size_t v1 = t.v[i];
            size_t v2 = t.v[(i + 1) % T::numVertices];

            // Store edges in a consistent order to avoid duplicates
            uniqueEdges.insert({std::min(v1, v2), std::max(v1, v2)}); 
        }
    }
    return uniqueEdges.size();
}


template <typename T>
size_t countUniqueTriangles(const Mesh<T>& mesh) {
    std::unordered_set<Triangle, TriangleHash> uniqueTriangles; // Use an unordered_set to store unique triangles   
    // Iterate through all tetrahedra and add their triangles to the set
    for (const auto& t : mesh.elements) {
        for (size_t i = 0; i < T::numVertices; ++i) {
            size_t v1 = t.v[i];
            size_t v2 = t.v[(i + 1) % T::numVertices];
            size_t v3 = t.v[(i + 2) % T::numVertices];
            // Store triangles in a consistent order to avoid duplicates
            uniqueTriangles.insert({std::min({v1, v2, v3}), std::min({std::max(v1, v2), std::max(v2, v3), std::max(v3, v1)}), std::max({v1, v2, v3})}); 
        }
    }
    return uniqueTriangles.size();
}


template <>
inline float calculateAspectRatio(const Mesh<Triangle>& mesh, const Triangle& t)  {
    // triangle lengths
    float a = mesh.vertices[t.v[0]].distance(mesh.vertices[t.v[1]]);
    float b = mesh.vertices[t.v[1]].distance(mesh.vertices[t.v[2]]);
    float c = mesh.vertices[t.v[2]].distance(mesh.vertices[t.v[0]]);

    // aspect ratio formula: (abc) / ((b+c-a)(c+a-b)(a+b-c))
    float num = a * b * c;
    float denom = (b+c - a) * (c+a - b) * (a+b - c);
    return num / denom;
}


template <>
inline float calculateAspectRatio(const Mesh<Tetrahedron>& mesh, const Tetrahedron& t)  {

    Point A = mesh.vertices[t.v[0]];
    Point B = mesh.vertices[t.v[1]];
    Point C = mesh.vertices[t.v[2]];
    Point D = mesh.vertices[t.v[3]];

    // triangle lengths
    float ab = A.distance(B);
    float ac = A.distance(C);
    float ad = A.distance(D);
    float bc = B.distance(C);
    float cd = C.distance(D);
    float da = D.distance(A);

    // aspect ratio formula
    float hMax = std::max({ab, ac, ad, bc, cd, da});
    float alpha = (B - A).dot((C - A).cross(D - A));

    Point normal_abc = (B - A).cross(C - A);
    Point normal_acd = (C - A).cross(D - A);
    Point normal_adb = (D - A).cross(B - A);
    Point normal_bcd = (C - B).cross(D - B);

    float r = std::abs(alpha) / (normal_abc.length() + normal_acd.length() + normal_adb.length() + normal_bcd.length());
    float quality = hMax / (2 * std::sqrt(6) * r);
    return quality;
}


template <typename T>
void calculateAspectRatios(Mesh<T>& mesh) {
    mesh.ratios.clear();

    // Calculate aspect ratio for each element and store in the ratios vector
    for (const auto& t : mesh.elements) {
        mesh.ratios.push_back(calculateAspectRatio<T>(mesh, t));
    }
}



// Display analysis

template <>
inline void analyzeMesh(Mesh<Triangle>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique edges : " << countUniqueEdges<Triangle>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<Triangle>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}


template <>
inline void analyzeMesh(Mesh<Tetrahedron>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique triangles : " << countUniqueTriangles<Tetrahedron>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<Tetrahedron>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}