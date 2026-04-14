cd "$(dirname "$0")/.."

echo "Compilation in progress..."

cmake -B build
cmake --build build --target analyzer --config Release

if [ -f "./build/analyzer3D" ]; then
    ./build/analyzer3D
elif [ -f "./build/Release/analyzer3D" ]; then
    ./build/Release/analyzer3D
else
    echo "Error: Executable not found."
fi

paraview output.vtk