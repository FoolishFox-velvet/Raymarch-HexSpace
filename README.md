# Raymarching Hextunnel

A real-time 3D raymarching shader demo built with C++, Raylib, and GLSL. The project renders an infinite hexagonal prism field with domain repetition, wave distortion, dynamic color palettes, and interactive first-person camera controls.

## Features

- Real-time sphere-tracing (raymarching) in GLSL 330
- Signed Distance Field (SDF) hexagonal prism geometry with infinite domain repetition
- First-person 3D camera with yaw/pitch rotation and 6-DOF movement
- Toggleable time-based color palette modulation

## Controls

| Key / Input | Action |
| :--- | :--- |
| `W` `A` `S` `D` | Move forward, left, backward, right |
| `Space` | Move up |
| `Left Shift` | Move down |
| `Mouse` | Look around (pitch and yaw) |
| `L` | Toggle color palette modulation |
| `ESC` | Exit application |

## Prerequisites

- A C++17 compatible compiler (GCC, Clang, or MSVC)
- [Raylib](https://www.raylib.com/) (4.0 or higher)
- OpenGL 3.3+ compatible GPU

## Build & Run

Make sure `shader.fs` is located in the same directory as the compiled executable.

**Linux (GCC):**
```bash
g++ main.cpp -o app -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./app
```
**MacOS (Clang)**
```bash
clang++ main.cpp -o app -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
./app
```
**Windows (MinGW)**
```bash
g++ main.cpp -o app.exe -lraylib -lopengl32 -lgdi32 -lwinmm
app.exe
```


