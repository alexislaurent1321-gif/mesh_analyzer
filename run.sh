echo "Compilation en cours..."

cmake -B build
cmake --build build --config Release

if [ -f "./build/mesh_analyzer" ]; then
    ./build/mesh_analyzer
elif [ -f "./build/Release/mesh_analyzer" ]; then
    ./build/Release/mesh_analyzer
else
    echo "Erreur : Exécutable introuvable."
fi