<p align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/6295/6295417.png" width="100" />
</p>
<p align="center">
    <h1 align="center">FOURIER-SERIES-WAVE-CIRCLES-ANIMATION-GRAPHICS-PROJECT</h1>
</p>

<p align="center">
	<!-- <img src="https://img.shields.io/github/license/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project?style=flat&color=0080ff" alt="license"> -->
	<img src="https://img.shields.io/github/last-commit/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project?style=flat&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project?style=flat&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project?style=flat&color=0080ff" alt="repo-language-count">
<p>
<p align="center">
		<em>Developed with the software and tools below.</em>
</p>
<p align="center">
	<img src="https://img.shields.io/badge/C-A8B9CC.svg?style=flat&logo=C&logoColor=black" alt="C">	
	<img src="https://img.shields.io/badge/CMake-064F8C.svg?style=flat&logo=CMake&logoColor=white" alt="CMake">

</p>
<hr>

## Overview

This project visualizes the Fourier Series through a dynamic wave and circle animation, demonstrating how complex waveforms can be constructed by summing simple sine waves. The animation graphically represents the Fourier transform, helping users to understand the mathematical concept in a more intuitive way.

---

## Table of Contents

> - [Overview](#overview)
> - [Features](#features)
> - [Repository Structure](#repository-structure)
> - [Getting Started](#getting-started)
>   - [Prerequisites](#prerequisites)
>   - [Installation](#installation)
>   - [Running Fourier-Series-Wave-Circles-Animation-Graphics-Project](#running-fourier-series-wave-circles-animation-graphics-project)
> - [Configuration](#configuration)
> - [Documentation](#documentation)
> - [Demo](#demo)
> - [Troubleshooting](#troubleshooting)
> - [Contributing](#contributing)

---

## Features

- **Fourier Series Visualization:** Demonstrates the breakdown of complex waveforms.
- **Interactive Animation:** Allows users to observe the creation of waves in real-time.
- **Modular Code:** Easily extendable to other types of waveforms.

---

## Repository Structure

```sh
└── Fourier-Series-Wave-Circles-Animation-Graphics-Project/
    ├── CMakeLists.txt
    ├── README.md
    ├── Videos
    │   ├── Circle_1.mp4
    │   ├── Circle_2.mp4
    │   ├── Circle_3.mp4
    │   ├── Circle_4.mp4
    │   ├── Circle_5.mp4
    │   ├── Circle_6.mp4
    │   ├── Circle_7.mp4
    │   ├── Circle_8.mp4
    │   └── Circle_9.mp4
    ├── build
    │   ├── .cmake
    │   ├── CMakeCache.txt
    │   ├── CMakeFiles
    │   ├── Makefile
    │   ├── cmake_install.cmake
    │   ├── compile_commands.json
    │   └── lib
    ├── include
    │   ├── constant.h
    │   ├── draw.h
    │   └── utils.h
    ├── lib
    │   ├── CMakeLists.txt
    │   ├── cmake_install.cmake
    │   ├── glad
    │   └── glfw-3.4
    └── src
        └── Fourier Seriess
            ├── constant.cpp
            ├── draw.cpp
            ├── main.cpp
            └── utils.cpp
```

---

## Getting Started

### Prerequisites

Before you begin, ensure you have the following software installed on your system:

- **C++ Compiler**: g++ or clang++
- **CMake**: A tool to generate the build files.
- **Graphics Library**: Ensure you have OpenGL or an equivalent graphics library installed to render the animation.

### Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project.git
   ```

2. **Navigate to the project directory:**

   ```bash
   cd Fourier-Series-Wave-Circles-Animation-Graphics-Project
   ```

3. **Create a Build Directory**:

   ```bash
   mkdir build
   cd build
   ```

4. **Generate Makefiles or Project Files**:
   Run CMake to generate the necessary build files:

   ```bash
   cmake ..
   ```

   - `..` tells CMake to use the `CMakeLists.txt` file in the parent directory.
   - You can also specify a generator (e.g., `-G "Unix Makefiles"`), but CMake typically auto-selects the appropriate one for your platform.

5. **Build the Project**:
   Once CMake has generated the build files, compile the project by running:

   ```bash
   cmake --build .
   ```

   Alternatively, you can use `make` if you're using Unix Makefiles:

   ```bash
   make
   ```

6. **Run the Executable**:
   After building, you'll find the executable in the build directory (usually in the `build/` or `build/Debug/` or `build/Release/` directories). Run it with:

   ```bash
   ./Graphics_Project.exe
   ```

   <p align="center">or</p>

   ```bash
   ./Debug/Graphics_Project.exe
   ```

### Running Fourier-Series-Wave-Circles-Animation-Graphics-Project

1. Use the following command to run Fourier-Series-Wave-Circles-Animation-Graphics-Project:

```bash
./Graphics_Project.exe
```

<p align="center">or</p>

```bash
./Debug/Graphics_Project.exe
```

2. Input the number of the circle you want to simulate.The number of circle must be ni range of (1-9)

---

## Configuration

Configuration options can be modified in the `main.cpp` or other relevant source files for adjusting the wave parameters, such as the number of harmonics or the speed of the animation.

---

## Documentation

For detailed information on the Fourier Series and its implementation in this project, refer to the comments within the source code files (`constant.cpp`, `draw.cpp`, `utils.cpp`, `main.cpp`).

---

## Demo

Refer to the [`Videos`](./Videos/) folder in the repository for example animations.

---

## Troubleshooting

- **Build Errors:** Ensure all dependencies are installed and configured correctly.
- **Animation Issues:** Check the graphics settings and ensure your hardware supports the required features.

---

## Contributing

Contributions are welcome! Here are several ways you can contribute:

- **[Submit Pull Requests](https://github.com/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.
- **[Join the Discussions](https://github.com/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project/discussions)**: Share your insights, provide feedback, or ask questions.
- **[Report Issues](https://github.com/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project/issues)**: Submit bugs found or log feature requests for Fourier-series-wave-circles-animation-graphics-project.

<details closed>
    <summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your GitHub account.
2. **Clone Locally**: Clone the forked repository to your local machine using a Git client.
   ```sh
   git clone https://github.com/Eemayas/Fourier-Series-Wave-Circles-Animation-Graphics-Project
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to GitHub**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.

Once your PR is reviewed and approved, it will be merged into the main branch.

</details>

---
