# OpenGLTK

## What OpenGLTK *is*:

OpenGLTK (or **OpenGL** **T**ool **K**it) is a static library for C++20 that abstracts OpenGL functionality into
higher-level constructs.
It sits in the middle-ground between pure OpenGL and SDL and was designed for quickly scaffolding graphics applications
while leaving the architecture and core game-loop up to developers.

It provides:

- A baseline shader class.
- Vertex struct definitions.
- Helper functions for IO operations like loading textures.
- Class abstractions for OpenGL buffers.
- RAII-style memory management.
- Helper functions for working with OpenGL "objects".

## What OpenGLTK *isn't*:

- **An OpenGL function loader**. Glad is required and must be supplied by the developer(s) for any projects using
  OpenGLTK.
- **A window manager**. Use GLFW or SDL2 for window management, or handle yourself with native APIs.
- **Input handler**. See above.
- **Abstractions for drawing primitives**. OpenGLTK supplies interfaces for implementing drawable objects but doesn't
  provide
  functions to do drawing directly.

## Quickstart

At the moment, **OpenGLTK is only available in source form**. If your project uses CMake, integration will be very
straight
forward. If not, you'll need to compile the library using CMake and link the static library to your non-CMake project.
You'll
also need to copy over the necessary headers (located
in [Source/](https://github.com/jakerieger/OpenGLTK/tree/master/Source)).

### Using in a CMake Project

OpenGLTK can be integrated into your CMake project by simply cloning the source to your project root and adding the
folder as a subdirectory to your main CMakeLists.txt:

```bash
# Clone method
~/Code/MyProject> git clone https://github.com/jakerieger/OpenGLTK.git --recurse-submodules

# Submodule method
~/Code/MyProject> git submodule add https://github.com/jakerieger/OpenGLTK.git
~/Code/MyProject> git submodule update --init --recursive
```

#### CMakeLists.txt

```cmake
project(MyProject)
add_subdirectory(OpenGLTK)
include_directories(
        ${CMAKE_SOURCE_DIR}/OpenGLTK/Source
        ...
)
add_executable(MyProject ...)
target_link_libraries(MyProject PRIVATE OpenGLTK)
```

#### Example Code

```c++
#include <OpenGLTK/OpenGLTK.h>

int main() {
    // GLFW/SDL and OpenGL initialization
    
    ...
    
    // Create a shader instance
    const auto shader = std::make_unique<GLTK::Shader>(
        Path("Assets/Shaders/Sprite.vert",
        Path("Assets/Shaders/Sprite.frag")
    );
    
    // Load a texture
    int texWidth, texHeight;
    const auto spriteTex = GLTK::LoadTexture("Assets/Sprites/Player.png", &texWidth, &texHeight);
    
    // Game loop
    while (running) {
        shader->Bind();
        shader->SetInt("uSprite", 0);
        
        // Draw sprite
        
        GLTK::Shader::Unbind();
    }

    return 0;
}
```

## License

OpenGLTK is licensed under the [ISC License](LICENSE). See [ThirdParty/LICENSES](ThirdParty/LICENSES) for third party
license information.