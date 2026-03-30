cmake_minimum_required(VERSION 3.20)
project(meshAnalyzer LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)

FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
)

FetchContent_MakeAvailable(tinyobjloader)

add_executable(mesh_analyzer 
    src/main.cpp 
    src/point.cpp
    src/mesh.cpp
) 

target_include_directories(mesh_analyzer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) 

target_link_libraries(mesh_analyzer PRIVATE tinyobjloader)