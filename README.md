# OpenGLTK

## What OpenGLTK *is*:

OpenGLTK (or **OpenGL** **T**ool **K**it) is a library that abstracts OpenGL functionality into higher-level constructs.
It sits in the middle-ground between pure OpenGL and SDL and was designed for quickly scaffolding graphics applications
while leaving the architecture and core game-loop up to developers.

It provides:

- A baseline shader class
- Vertex struct definitions
- Helper functions for IO operations like loading textures
- Class abstractions for OpenGL buffers
- RAII-style memory management
- Helper functions for working with OpenGL "objects"

## What OpenGLTK *isn't*:

- **An OpenGL function loader**. Glad is required and must be supplied by the developer(s) for any projects using
  OpenGLTK.
- **A window manager**. Use GLFW or SDL2 for window management, or handle yourself with native APIs.
- **Input handler**. See above.
- **Abstractions for drawing primitives**. OpenGLTK supplies interfaces for implementing drawable objects but doesn't
  provide
  functions to do drawing directly.