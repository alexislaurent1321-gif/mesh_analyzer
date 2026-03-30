[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://alexislaurent1321-gif.github.io/mesh_evaluation/)

# Mesh analyzer

## hashing

## Aspect ratio formula


# Installation

## Dependencies
The library uses the vcpkg package manager to load external libraries. To install, install **vcpkg** in the `C:/` folder.
Then, install the libraries using the following instructions :

```bash
cd /
cd vcpkg
vcpkg install tinyobjloader:x64-windows
```
Use the following include paths in the `cpp_properties.json` : 
```
"includePath": [
                "${workspaceFolder}/**",
                "C:\\vcpkg\\installed\\x64-windows\\include",
                "include/**"
            ],
```

## Compilation and execution

Compilation on Windows, preferably with **MSVC**. Use the **VS Code** interface if possible.
