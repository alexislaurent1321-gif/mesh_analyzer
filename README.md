[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://alexislaurent1321-gif.github.io/mesh_analyzer/)

# Mesh generation
Start of a project to analyze a mesh and triangulate a 2D space.

# Project structure
The project is organized into the following folders: 
- **geometry :** contains classes for Point, Triangle, Mesh
- **mesh_generation :** contains classes for generating grids or triangulate a set of vertices
- **visualization :** contains the export in VTK format for ParaView


# Features
## Mesh analyzer
The mesh analysis section allows you to view its attributes and detect/highlight edges.

#### hashing
To ensure optimal search performance within the graph and avoid duplicate edges, we construct a hash table. This method involves using a `std::unordered_set` structure with a custom hash function to identify unique edges with an average time complexity of $O(1)$.

#### Exemple
Here, an exemple for a cube : 
```bash
Vertices : 8
Triangles : 12
Unique edges : 18
```

#### Aspect ratio 

The analyzer computes also the aspects ratio of triangles : 
```bash
min aspect ratio : 1.20711
max aspect ratio : 1.20711
mean aspect ratio : 1.20711
```

The triangles that make up a cube are isosceles-right triangles, which corresponds to an aspect ratio of $\simeq 1.2$.


Let there be a triangle with sides a, b, and c. The formula is

$$\frac{abc}{(b+c-a)(c+a-b)(a+b-c)}$$

This is a basic finite element formula : 
- a ratio of 1 corresponds to a perfect equilateral triangle.
- the higher the ratio, the more distorted the triangle becomes, which can hinder the convergence of the solvers.
  
Here is an example with a cube and a stretched cube. Since the side faces are stretched, the result is larger : 

<table>
  <tr>
    <td><img width="600" height="300" alt="cube_ratios" src="https://github.com/user-attachments/assets/aeea27de-0dd5-40a6-b300-3f0f8b586e1b" />
    <td><img width="600" height="300" alt="cube2_ratios" src="https://github.com/user-attachments/assets/75ffb92b-da42-4868-8ef9-5d5246ebd412" />
  </tr>
</table>

## Boundaries detection
Another function of this project is to detect the edges of the mesh if it is open. To do this, we select the edges along the boundary. An edge is considered to belong to the boundary of the region if it belongs to exactly one triangle. 
To evaluate the valence of the edges (the number of triangles they belong to), we create a `std::unordered_map` that stores integers as values and edges as keys. We iterate through the edges of each triangle and increment the value corresponding to the evaluated edge by 1.

The example used here is a hemisphere with some missing faces. Part of the edge, as well as two triangles sharing a common vertex, have been removed. 

<img width="600" height="400" alt="demi_sphere_boundaries" src="https://github.com/user-attachments/assets/171883d1-4b31-4704-8ced-66f49e6d964d" style="width:50%;" /> 



The results show that all edges are detected.

## Smoothing
A useful method for improving the regularity of a mesh is to apply smoothing. The function depends here on the number of iterations and a factor $\lambda$. 

$$v_i \longleftarrow v_i + \lambda \left( \frac{1}{N_i}\sum_{j=1}^{N_i} v_j - v_i \right)$$

if $\lambda = 1$, the new position corresponds simply to the mean of neighbourghs' positions : 

$$v_i \longleftarrow \frac{1}{N_i}\sum_{j=1}^{N_i} v_j$$

Here is an example of a cube with $\lambda=1$ and $10$ iterations : 

<img width="1209" height="600" alt="cube_smooth" src="https://github.com/user-attachments/assets/aac01706-2f8b-4704-a0aa-ee5772952bb7" style="width:50%;" />

## Delaunay triangulation
The final feature, which will be at the heart of the project, involves triangulating a set of points using the Delaunay method. The algorithm used here is the Bowyer-Watson algorithm. 
### Test on a regular grid
To validate the triangulation, we count the number of triangles and edges and check the ratio. Since the mesh is a grid, we expect a constant ratio of $\simeq 1.2$. Here are the results for a $4\times 4$ grid : 
```
Vertices : 25
Triangles : 32
Unique edges : 56
min aspect ratio : 1.20711
max aspect ratio : 1.20711
mean aspect ratio : 1.20711
```
The results are correct.
> [!WARNING]  
The VTK export isn't working for this part of the project at the moment. I'll fix it as soon as possible.


# Upcoming changes
### as soon as possible
- **Replace the main file with demos** to test various cases and features of the project separately. Add an error handler.
- fix bug of the VTK export
- Test triangulation on an irregular set of points
### in the short term
- **mesh refinement :** division of triangles with an incorrect aspect ratio
- **local mesh adjustments :** remove triangles from the mesh, especially if the model contains a hole or is not convex.
### in the longer term
- support for 3D meshes
- retopology
- **mesh simplification :** edge collapse ([A Comprehensive Guide to Mesh Simplification
using Edge Collapse](https://arxiv.org/pdf/2512.19959)) (maybe)


# Compilation and execution

Compilation on Windows (preferably with **MSVC**) or Linux. Use the **VS Code** interface if possible.

### Dependencies
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) (included in the code)
- [ParaView](https://www.paraview.org/)
