// Author: Jake Rieger
// Created: 9/23/2024.
//

#include "Shader.h"
#include "Types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <TextureLoader.h>

GLFWwindow* gWindow;

int main() {
    if (!glfwInit()) {
        Panic("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gWindow = glfwCreateWindow(800, 600, "Testbed (x64)", None, None);
    if (!gWindow) {
        glfwTerminate();
        Panic("Failed to create GLFW window.");
    }

    glfwMakeContextCurrent(gWindow);

    if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        Panic("Failed to initialize GLAD.");
    }

    glViewport(0, 0, 800, 600);

    auto texture = GLTK::LoadTexture("Assets/Textures/circle.png");
    auto shader =
      new GLTK::Shader(Path("Assets/Shaders/Sprite.vert"), Path("Assets/Shaders/Sprite.frag"));

    while (!glfwWindowShouldClose(gWindow)) {
        glfwPollEvents();
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update code
        {}

        // Render code
        {
            shader->Bind();

            GLTK::Shader::Unbind();
        }

        glfwSwapBuffers(gWindow);
    }

    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}