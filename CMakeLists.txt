cmake_minimum_required(VERSION 3.20)
project(meshAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mesh_analyzer 
    src/geometry/triangle.cpp
    src/geometry/point.cpp

    src/mesh/mesh.cpp
    src/mesh/mesh_analysis.cpp
    src/mesh/mesh_smoothing.cpp
    src/mesh/mesh_basic_shapes.cpp
    src/mesh/mesh_triangulation.cpp

    src/io/exportToVTK.cpp
    src/io/loadObj.cpp
)

target_include_directories(mesh_analyzer PUBLIC include)


# Demos

add_executable(analyzer demos/analyzer.cpp)
target_link_libraries(analyzer PRIVATE mesh_analyzer)

add_executable(smoothing demos/smoothing.cpp)
target_link_libraries(smoothing PRIVATE mesh_analyzer)

add_executable(triangulation demos/triangulation.cpp)
target_link_libraries(triangulation PRIVATE mesh_analyzer)
