cmake_minimum_required(VERSION 3.20)
project(meshAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(mesh_analyzer 
    src/main.cpp 
    src/point.cpp
    src/mesh.cpp
)

# Il suffit de dire à CMake d'aller voir dans /include
target_include_directories(mesh_analyzer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)