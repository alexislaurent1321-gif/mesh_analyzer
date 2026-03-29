@echo off
echo Compilation

cmake -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release   
.\build\Release\mesh_analyzer.exe    