# Computer Graphics Suite

A comprehensive suite of university projects implementing key computer graphics algorithms, rendering techniques, and 3D pipelines. Developed using **C++20/OpenGL/GLFW** and **Python/PyOpenGL**, this repository progresses from fundamental 3D coordinate plotting and camera systems to advanced light/material simulation and binary texture mapping.

---

## Table of Contents
- [Project 1: Parametric 3D Surface Generator (Python)](#project-1-parametric-3d-surface-generator-python)
- [Project 2: Interactive Camera & Model Transformation (C++)](#project-2-interactive-camera--model-transformation-c)
- [Project 3: Advanced Illumination & Shading Models (C++)](#project-3-advanced-illumination--shading-models-c)
- [Project 4: Custom TGA Texture Mapping System (C++)](#project-4-custom-tga-texture-mapping-system-c)

---

## Project 1: Parametric 3D Surface Generator (Python)

### Description
An introductory project implementing a 3D model generator that mathematically calculates and renders a parametric egg-like surface. Using a specified 5th-degree polynomial mapping function, the application dynamically generates 3D vertex coordinate arrays spanning a normalized $(u, v)$ grid. It features interactive viewing modes, color interpolation, and rotation animations.

### Highlights & Implementation Details
- **Mathematical Modeling:** Generates a 3D surface using parametric equations mapped across a $[0, 1] \times [0, 1]$ grid.
- **Multiple Rendering Pipelines:** Supports switching in real time between drawing vertices as **Points**, **Lines (Wireframe)**, and filled **Triangles** using runtime keyboard callbacks.
- **Interactive Controls:**
  - `1` / `P`: Point Cloud Mode
  - `2` / `L`: Wireframe Mode
  - `3` / `T`: Triangulated Solid Mode
  - `4` / `S`: Shaded/Colored Mesh Mode

### Technologies
- **Python 3**
- **PyOpenGL** & **GLU** (Graphics rendering)
- **GLFW** (Windowing and event handling)
- **NumPy** (High-performance multi-dimensional array math)

### Run Instructions
1. Navigate to the project directory:
   ```bash
   cd 1
   ```
2. Install the required dependencies:
   ```bash
   pip install numpy glfw PyOpenGL
   ```
3. Execute the program:
   ```bash
   python3 main.py
   ```

### Showcase / Gallery
<img src="assets/placeholder.png" width="48%" />
<img src="assets/placeholder.png" width="48%" />

---

## Project 2: Interactive Camera & Model Transformation (C++)

### Description
A high-performance C++ implementation of the parametric 3D model generator, expanding on the concepts from Project 1. This project introduces a robust, dual-mode transformation matrix system that permits user interaction with either the model's transformation matrices (translation, rotation, scale) or a fully dynamic virtual camera system navigating spherical coordinates.

### Highlights & Implementation Details
- **Dual-Mode Control Paradigm:** Toggle between modes using the `M` key:
  - **Model Mode:** Directly rotate (X/Y axes) and scale the rendered 3D egg model using the mouse.
  - **Camera Mode:** Orbit, zoom, and sweep a virtual camera in 3D space using spherical coordinate transformations ($\theta$, $\phi$, $r$) bound to mouse inputs.
- **View Matrix Transformations:** Dynamically re-calculates camera-to-world transformations using `gluLookAt` and custom mouse gesture velocity vectors.

### Technologies
- **C++20**
- **OpenGL** & **GLU**
- **GLFW3** (Window management, keyboard/mouse event dispatching)
- **CMake** (Build system)

### Compilation & Build Instructions
1. Navigate to the project directory:
   ```bash
   cd 2
   ```
2. Generate build configuration files and compile:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the application:
   ```bash
   ./2
   ```

### Showcase / Gallery
<img src="assets/placeholder.png" width="48%" />
<img src="assets/placeholder.png" width="48%" />

---

## Project 3: Advanced Illumination & Shading Models (C++)

### Description
An advanced computer graphics simulation modeling light interactions and shading behaviors over complex 3D meshes. The project computes analytical vertex normals to simulate Phong/Lambertian illumination, supporting specular highlight calculations, ambient lighting, and interactive multi-source light orbital movements.

### Highlights & Implementation Details
- **Analytical Normal Vector Derivation:** Rather than approximating normals, this project derives exact mathematical surface normal vectors $(\mathbf{n_x}, \mathbf{n_y}, \mathbf{n_z})$ by taking the partial derivatives ($x_u, x_v, y_u, y_v, z_u, z_v$) of the parametric model equations and applying cross-product and normalization steps.
- **Dual Light Source Setup:**
  - **Light 0 (Yellow):** Interactive orbit around the target mesh.
  - **Light 1 (Blue):** Independently controllable orbital light source.
- **Lighting Controls:** Allows interactive adjustments of light positions, diffuse/specular/ambient reflection constants, and material shininess values in real-time.

### Technologies
- **C++20**
- **OpenGL 1.1 / GLU** (Fixed-function lighting pipeline integration)
- **GLFW3**
- **CMake**

### Compilation & Build Instructions
1. Navigate to the project directory:
   ```bash
   cd 3
   ```
2. Build the executable:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the executable:
   ```bash
   ./3
   ```

### Showcase / Gallery
<img src="assets/placeholder.png" width="48%" />
<img src="assets/placeholder.png" width="48%" />

---

## Project 4: Custom TGA Texture Mapping System (C++)

### Description
A system demonstrating 3D texture mapping, texture coordinates, and custom file loaders. The application features a lightweight, binary TGA (Truevision Targa) image file parser that reads and loads raw asset data directly into OpenGL's texture state machine, mapping them onto complex 3D geometry with back-face culling optimizations.

### Highlights & Implementation Details
- **Custom Binary TGA Image Parser (`loadTGA`):** Opens raw `.tga` files, decodes the binary header (extracting width, height, and bits-per-pixel indices supporting 24-bit BGR and 32-bit BGRA formats), copies the payload, and binds them to the active OpenGL texture buffer.
- **Advanced Texture Mapping:** Uses UV coordinate coordinates (`glTexCoord2f`) mapped to vertex triangles to draw complex texture orientations.
- **Rendering Performance Optimizations:** Employs back-face culling (`GL_CULL_FACE`, `GL_BACK`) to cull non-visible triangles and optimize overall GPU rendering pipelines.
- **Interactive Multi-Texture Toggling:** Dynamically switches applied textures between loaded files in real-time.

### Technologies
- **C++20**
- **OpenGL & GLU**
- **GLFW3**
- **Binary File I/O** (C++ File Streams)
- **CMake**

### Compilation & Build Instructions
1. Navigate to the project directory:
   ```bash
   cd 4
   ```
2. Build the project (CMake will copy the TGA textures from the `/resources` directory to the target binary build folder automatically):
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the executable:
   ```bash
   ./4
   ```

### Showcase / Gallery
<img src="assets/placeholder.png" width="48%" />
<img src="assets/placeholder.png" width="48%" />
