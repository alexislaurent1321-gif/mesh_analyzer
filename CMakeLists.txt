cmake_minimum_required(VERSION 3.20)
project(meshAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(mesh_analyzer 
    src/geometry/triangle.cpp
    src/geometry/point.cpp
    src/geometry/mesh.cpp
    src/visualization/exportToVTK.cpp
    src/mesh_generation/basic_shapes.cpp
    src/mesh_generation/triangulation.cpp
    src/main.cpp
)

target_include_directories(mesh_analyzer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)