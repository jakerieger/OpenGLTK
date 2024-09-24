// Author: Jake Rieger
// Created: 9/23/2024.
//

#include "OpenGLTK.h"

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

    const auto texture = GLTK::LoadTexture("Assets/Textures/circle.png");
    const auto shader =
      GLTK::Shader::Create(Path("Assets/Shaders/Sprite.vert"), Path("Assets/Shaders/Sprite.frag"));
    const auto camera = GLTK::CreateCamera<GLTK::OrthoCamera>(800, 600);

    while (!glfwWindowShouldClose(gWindow)) {
        glfwPollEvents();
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update code
        { camera->Update(); }

        // Render code
        {
            shader->Bind();

            auto mvp = camera->GetViewProjection() * glm::mat4(1.f);

            GLTK::Shader::Unbind();
        }

        glfwSwapBuffers(gWindow);
    }

    GLTK::DeleteTexture(texture);

    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}