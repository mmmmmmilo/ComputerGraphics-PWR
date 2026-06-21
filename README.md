# Computer Graphics: University Projects

A comprehensive suite of university coursework implementations focusing on key computer graphics algorithms, rendering techniques, and 3D pipelines. Developed using **C++20/OpenGL/GLFW** and **Python/PyOpenGL**, this repository progresses from fundamental 3D coordinate plotting and camera systems to advanced light/material simulation and binary texture mapping.

## Repository Overview

This repository acts as a centralized suite containing one Python and three standalone C++ projects. Each project demonstrates progressive concepts in computer graphics, from basic parametric surfaces to custom texture parsers.

1. **Project 1: Parametric 3D Surface Generator (Python):** Mathematically calculates and renders a parametric egg-like surface using PyOpenGL.
2. **Project 2: Interactive Camera & Model Transformation (C++):** Introduces a dual-mode transformation matrix system for model manipulation and virtual camera navigation.
3. **Project 3: Advanced Illumination & Shading Models (C++):** Computes analytical vertex normals to simulate illumination, specular highlights, and dynamic light sources.
4. **Project 4: Custom TGA Texture Mapping System (C++):** Features a custom binary TGA image parser to load and map textures onto 3D geometry with back-face culling.

---

## Project 1: Parametric 3D Surface Generator (Python)

### Description
An introductory project implementing a 3D model generator that mathematically calculates and renders a parametric egg-like surface. Using a specified 5th-degree polynomial mapping function, the application dynamically generates 3D vertex coordinate arrays spanning a normalized $[0, 1] \times [0, 1]$ grid. It features interactive viewing modes, color interpolation, and rotation animations.

### Highlights & Implementation Details
* **Mathematical Modeling:** Generates a 3D surface using parametric equations mapped across a grid.
* **Multiple Rendering Pipelines:** Supports switching in real time between drawing vertices as **Points**, **Lines (Wireframe)**, and filled **Triangles** using runtime keyboard callbacks.
* **Interactive Controls:**
  * `1` / `P`: Point Cloud Mode
  * `2` / `L`: Wireframe Mode
  * `3` / `T`: Triangulated Solid Mode
  * `4` / `S`: Shaded/Colored Mesh Mode

### Showcase
<img width="80%" alt="opengl1" src="https://github.com/user-attachments/assets/1795311d-e501-4674-ae5d-b875512dd304" />

---

## Project 2: Interactive Camera & Model Transformation (C++)

### Description
A high-performance C++ implementation of the parametric 3D model generator, expanding on the concepts from Project 1. This project introduces a dual-mode transformation matrix system that permits user interaction with either the model's transformation matrices (translation, rotation, scale) or a fully dynamic virtual camera system navigating spherical coordinates.

### Highlights & Implementation Details
* **Dual-Mode Control Paradigm:**
  * **Model Mode:** Directly rotate (X/Y axes) and scale the rendered 3D egg model using the mouse.
  * **Camera Mode:** Orbit, zoom, and sweep a virtual camera in 3D space using spherical coordinate transformations $(\theta, \phi, r)$ bound to mouse inputs.
* **View Matrix Transformations:** Dynamically re-calculates camera-to-world transformations using `gluLookAt` and custom mouse gesture velocity vectors.
* **Interactive Controls:**
  * `M`: Toggle the active control paradigm between **Model Mode** and **Camera Mode**.
  * `LMB Drag` / `RMB Drag`: Rotate (X/Y axes) and scale the rendered 3D model (in Model Mode), or orbit, zoom, and sweep the virtual camera (in Camera Mode).

### Showcase 
<img width="80%" alt="opengl2" src="https://github.com/user-attachments/assets/2eb3fadb-9191-4c77-8d83-6d77872449b8" />

---

## Project 3: Advanced Illumination & Shading Models (C++)

### Description
An advanced computer graphics simulation modeling light interactions and shading behaviors over complex 3D meshes. The project computes analytical vertex normals to simulate illumination, supporting specular highlight calculations, ambient lighting, and interactive multi-source light orbital movements.

### Highlights & Implementation Details
* **Analytical Normal Vector Derivation:** Rather than approximating normals, this project derives exact mathematical surface normal vectors $(\mathbf{n_x}, \mathbf{n_y}, \mathbf{n_z})$ by taking the partial derivatives $(x_u, x_v, y_u, y_v, z_u, z_v)$ of the parametric model equations and applying cross-product and normalization steps.
* **Dual Light Source Setup:**
  * **Light 0 (Yellow):** Interactive orbit around the target mesh.
  * **Light 1 (Blue):** Independently controllable orbital light source.
* **Interactive Controls:**
  * `Left Mouse Button + Drag`: Orbit the currently selected light source around the 3D mesh.
  * `Space`: Toggle the active light source for editing (switches between Light 0 and Light 1).
  * `R` / `G` / `B`: Select the specific color channel (Red, Green, or Blue) to modify.
  * `+` / `-`: Increase or decrease the intensity of the selected color channel for the active light.

### Showcase
<img width="80%" alt="opengl3" src="https://github.com/user-attachments/assets/f57649f3-ee73-4aa9-9d2a-0314d7a57557" />

---

## Project 4: Custom TGA Texture Mapping System (C++)

### Description
A system demonstrating 3D texture mapping, texture coordinates, and custom file loaders. The application features a lightweight, binary TGA image file parser that reads and loads raw asset data directly into OpenGL's texture state machine, mapping them onto complex 3D geometry with back-face culling optimizations.

### Highlights & Implementation Details
* **Custom Binary TGA Image Parser (`loadTGA`):** Opens raw `.tga` files, decodes the binary header (extracting width, height, and bits-per-pixel indices supporting 24-bit BGR and 32-bit BGRA formats), copies the payload, and binds them to the active OpenGL texture buffer.
* **Advanced Texture Mapping:** Uses UV coordinate mapping (`glTexCoord2f`) applied to vertex triangles to draw complex texture orientations.
* **Rendering Performance Optimizations:** Employs back-face culling (`GL_CULL_FACE`, `GL_BACK`) to cull non-visible triangles and optimize overall GPU rendering pipelines.
* **Interactive Multi-Texture Toggling:** Dynamically switches applied textures between loaded files in real-time.
* **Interactive Controls:**
  * `Left Mouse Button + Drag`: Rotate the 3D model/scene intuitively using mouse delta vectors.
  * `Space`: Dynamically swap the active mapped texture (toggles `use_texture2`).
  * `H`: Toggle the visibility of the front-facing wall (useful for inspecting back-face culling behavior).

### Showcase
<img width="80%" alt="opengl4" src="https://github.com/user-attachments/assets/df5d8780-e90f-483a-b177-c123a76dd457" />

---

## Compilation & Execution Instructions

### Prerequisites
Ensure the following tools are installed and accessible in your system's `PATH`:
* **C++ Compiler:** GCC 11+, or Clang 13+ (Linux) with C++20 support.
* **CMake:** Version 3.19 or newer.
* **Python Environment:** Python 3 with pip.

>Platform Support Note: This project is natively developed and tested on Linux. Windows compilation is not officially supported due to strict dependencies on Unix-like build environments and native package managers.

### Python Setup (Project 1)
Install the required dependencies via pip:
```bash
pip install numpy glfw PyOpenGL

```

### C++ Setup (Linux)

Install required dependencies for windowing, graphics, and OpenGL extensions. On Fedora, you can use:

```bash
sudo dnf install libX11-devel libXrandr-devel libXcursor-devel libXi-devel \
  mesa-libGL-devel mesa-libGLU-devel glfw-devel pkgconfig

```

Generate build files and compile the entire C++ suite:

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

```

### Running the Applications

Navigate to the root directory for Python, or the build folder to run the C++ projects:

#### Project 1 (Python)

* **Linux:** `python3 main.py` (Execute inside the specific Project 1 directory)

#### Projects 2, 3, and 4 (C++)

The executables are generated in the build directory. Run them directly from there based on the project you want to test (replace `<project_number>` with `2`, `3`, or `4`):

* **Linux:** `./<project_number>`
