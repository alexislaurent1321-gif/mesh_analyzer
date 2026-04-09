#!/bin/bash

# Move to the project root (one level up from /scripts)
cd "$(dirname "$0")/.." || exit

echo "Compilation in progress..."

# Configure and build
cmake -B build
cmake --build build --target triangulation --config Release

# Check for the executable in standard locations
if [ -f "./build/triangulation" ]; then
    ./build/triangulation
elif [ -f "./build/Release/triangulation" ]; then
    ./build/Release/triangulation
else
    echo "Error: Executable 'triangulation' not found."
    exit 1
fi

# Visualize output
if [ -f "output.vtk" ]; then
    paraview output.vtk
else
    echo "Error: output.vtk was not generated."
fi