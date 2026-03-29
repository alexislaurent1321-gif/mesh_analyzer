cmake_minimum_required(VERSION 3.20)
project(meshAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(tinyobjloader CONFIG REQUIRED)

add_executable(mesh_analyzer 
    src/main.cpp 
    src/point.cpp
    src/mesh.cpp
)

target_include_directories(mesh_analyzer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(mesh_analyzer PRIVATE tinyobjloader::tinyobjloader)