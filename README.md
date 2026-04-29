[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://alexislaurent1321-gif.github.io/Enmesh/)

# Enmesh
Project to analyze a triangular mesh or create one using Delaunay. 

This project is currently in the process of integrating 3D mesh management (created on [Gmsh](https://gmsh.info/)). 

The next step will be to implement more complex methods, such as constrained Delaunay. For more information, see the [Upcoming changes](#upcoming-changes) section.

# Project structure

```bash
+---demos           # demo main files to test different features of the project
+---extern          # extern libraries to parse files (submoules)
+---include 
|   +---geometry    # geometrical elements of a mesh
|   +---io          # input/output : functions to load and export meshes
|   \---mesh        # mesh class and processing functions (smoothing, triangulation, quality analysis)
+---models
+---scripts         # .bat and .sh files to compile and execute demos   
\---src
    +---geometry
    +---io
    \---mesh



```


# Features
## Mesh analyzer (`demo/demo_analyzer.cpp`)
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

#### Boundaries detection 
Another function of this project is to detect the edges of the mesh if it is open. To do this, we select the edges along the boundary. An edge is considered to belong to the boundary of the region if it belongs to exactly one triangle. 
To evaluate the valence of the edges (the number of triangles they belong to), we create a `std::unordered_map` that stores integers as values and edges as keys. We iterate through the edges of each triangle and increment the value corresponding to the evaluated edge by 1.

The example used here is a hemisphere with some missing faces. Part of the edge, as well as two triangles sharing a common vertex, have been removed. 

<img width="600" height="400" alt="demi_sphere_boundaries" src="https://github.com/user-attachments/assets/171883d1-4b31-4704-8ced-66f49e6d964d" style="width:50%;" /> 



The results show that all edges are detected.

### 3D version : `demo/demo_analyzer3D.cpp` : 
The demo allows you to do the same thing for a tetrahedral mesh. The missing step is to highlight the edge faces in ParaView. The selected format is .msh (version 4.1), the parser was chosen based on the library [mshio](https://github.com/qnzhou/MshIO.git) by qnzhou. Gmsh's Modern Format requires manually converting the format's tags into element indices. Here, we use the example of a sphere to calculate its statistics :

<img width="2193" height="1131" alt="sphere" src="https://github.com/user-attachments/assets/e7895227-b506-435d-a943-edff87fcb268" style="width:50%;" />

```bash
Vertices : 211
Elements : 709
Unique triangles : 1580
min aspect ratio : 1.0151
max aspect ratio : 4.0086
mean aspect ratio : 1.60255
boundaries triangles : 324
```
The aspect ratio is calculated using this formula: (https://docs.salome-platform.org/latest/gui/SMESH/aspect_ratio_3d.html)

The statistics match those of Gmsh :
<img width="361" height="268" alt="statistics" src="https://github.com/user-attachments/assets/7aa8f484-0913-4807-8609-b646647547c9" />




## Delaunay triangulation (`demo/demo_triangulation.cpp`)
The final feature, which will be at the heart of the project, involves triangulating a set of points using the Delaunay method. The algorithm used here is the [Bowyer-Watson](https://www.gorillasun.de/blog/bowyer-watson-algorithm-for-delaunay-triangulation/) algorithm. 
### Test on a regular grid
To validate the triangulation, we count the number of triangles and edges and check the ratio. Since the mesh is a grid, we expect a constant ratio of $\simeq 1.2$. Here are the results for a $4\times 4$ cells ($5 \times 5$ points) grid : 
```
Vertices : 25
Triangles : 32
Unique edges : 56
min aspect ratio : 1.20711
max aspect ratio : 1.20711
mean aspect ratio : 1.20711
```

<img width="1209" height="600" alt="grid_triangulated" src="https://github.com/user-attachments/assets/53eee18e-3077-4b87-9eea-634a993a1e06" style="width:50%;"/>

The results are correct.


## Smoothing (`demo/demo_smoothing.cpp`)
A useful method for improving the regularity of a mesh is to apply smoothing. The function depends here on the number of iterations and a factor $\lambda$. 

$$v_i \longleftarrow v_i + \lambda \left( \frac{1}{N_i}\sum_{j=1}^{N_i} v_j - v_i \right)$$

### Boundaries conditions
Using smoothing can improve the quality of a mesh, particularly that of flat 2D meshes. These meshes are always open, which poses a problem because all the vertices quickly converge toward the center to the point where the mesh may eventually disappear. The idea, therefore, is to avoid applying smoothing to the edge edges. 

Here, we take the example of a random set of points that we triangulate and then apply smoothing (until the result stops changing) to: 

<img width="1209" height="600" alt="smooth_before" src="https://github.com/user-attachments/assets/bb634cbb-85b9-46c1-9f07-0cf98881b850" style="width:50%;"/>

```bash
min aspect ratio : 1.00325
max aspect ratio : 104.116
mean aspect ratio : 4.64866
```

<img width="1209" height="600" alt="smooth_after" src="https://github.com/user-attachments/assets/c4aead62-9d83-4d45-9e70-0a6459ec679d" style="width:50%;"/>

```bash
min aspect ratio : 1.0123
max aspect ratio : 3.65891
mean aspect ratio : 1.50397
```
We observe a better average aspect ratio. However, this result can be further improved by refining certain triangles, which will be the next step in the project.


# Upcoming changes
### as soon as possible
- Finish the demo for 3D mesh analysis (display boundaries on ParaView)
- manually generate and triangulate basic shapes (grid, cylinder, disc) in the `basic_shapes` file
### in the short term
- **local mesh adjustments :** remove triangles from the mesh, especially if the model contains a hole or is not convex.
- see Constrained Delaunay triangulation
### in the longer term
- see advancing front method ([Advancing Front Grid
Generation](http://ebrary.free.fr/Mesh%20Generation/Handbook_of_Grid_%20Generation,1999/chap17.pdf))
- implement Delaunay for tetrhedral meshes
- **mesh simplification :** edge collapse ([A Comprehensive Guide to Mesh Simplification
using Edge Collapse](https://arxiv.org/pdf/2512.19959)) (maybe)


# Compilation and execution
To clone the project : 
```bash
git clone --recurse-submodules https://github.com/alexislaurent1321-gif/mesh_analyzer.git
```

Compilation on Windows (preferably with **MSVC**) or Linux. Use the **VS Code** interface if possible. On Windows, to run ParaView from the command line, add the ParaView bin folder (e.g., `C:\Program Files\ParaView 6.1.0\bin`) to the `PATH` environment variables.

The demos can be run in the `scripts` folder. Scripts are named as follows : `run_{demo}.sh` for Linux or `run_{demo}.bat` for Windows.

Use the following commands : 
- `./scripts/run_{demo}.bat` on Windows
- `bash scripts/run_{demo}.sh` or `wsl sh scripts/run_{demo}.sh` on Linux



### Dependencies
- [mshio](https://github.com/qnzhou/MshIO.git)
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader.git) 
- [ParaView](https://www.paraview.org/)
