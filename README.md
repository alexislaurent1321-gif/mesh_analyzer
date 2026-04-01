[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://alexislaurent1321-gif.github.io/mesh_evaluation/)

# Mesh analyzer
Start of the mesh generation project. For now, it involves evaluating the quality of a 2D triangular mesh and edge detection. This project will evolve in the coming weeks to include 2D and eventually 3D mesh generation.

## Mesh class
This is a 2D triangular mesh class. 

### hash function
To ensure optimal search performance within the graph and avoid duplicate edges, we construct a hash table. For now, it is simply used to count the number of edges in the graph.



## Aspect ratio formula
Let there be a triangle with sides a, b, and c. The formula is
$$ \frac{abc}{(b+c-a)(c+a-b)(a+b-c)} $$
A result of 1 corresponds to an equilateral triangle and it is greater than 1 by the amount that the triangle is distorted.

## Boundaries detection
Another function of this project is to detect the edges of the mesh if it is open. To do this, we select the edges along the boundary. An edge is considered to belong to the boundary of the region if it belongs to exactly one triangle. 

# Results
## Cube
To assess the quality of the triangles, we simply try the experiment on a cube and then on a stretched cube.

### cube
First, we check that the number of vertices, triangles, and edges matches the expected result
```bash
Vertices : 8
Triangles : 12
Unique edges : 18
```
These numbers are correct, particularly the number of vertices, which shows that the hashing worked. Next, we look at the quality of the triangles. We simply expect to get the same ratio for each of them : 

```bash
min aspect ratio : 1.20711
max aspect ratio : 1.20711
mean aspect ratio : 1.20711
```
<img width="600" height="300" alt="cube_ratios" src="https://github.com/user-attachments/assets/aeea27de-0dd5-40a6-b300-3f0f8b586e1b" />

### stretched cube
In this configuration, the height along the z-axis is doubled : 
```bash
min aspect ratio : 1.20711
max aspect ratio : 1.46353
mean aspect ratio : 1.37805
```
We make sure that we get a higher value on the side faces, since the triangles are more stretched : 
<img width="600" height="300" alt="cube2_ratios" src="https://github.com/user-attachments/assets/75ffb92b-da42-4868-8ef9-5d5246ebd412" />

## Boudaries detection

<img width="600" height="400" alt="demi_sphere_boundaries" src="https://github.com/user-attachments/assets/171883d1-4b31-4704-8ced-66f49e6d964d" />



# Upcoming changes
### in the coming days
- support for quad meshes
- domain boundary detection
### in the short term
- implementation of triangulation methods (starting with Delaunay)
### in the longer term
- 
- support for 3D meshes


## Compilation and execution

Compilation on Windows (preferably with **MSVC**) or Linux. Use the **VS Code** interface if possible.
