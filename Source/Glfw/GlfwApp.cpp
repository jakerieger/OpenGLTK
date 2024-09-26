// Author: Jake Rieger
// Created: 9/25/2024.
//

#include "GlfwApp.h"

#include <utility>
#include <Panic/Panic.h>

namespace GLTK {
    IGlfwApp::IGlfwApp(str title, int width, int height)
        : mWindowTitle(std::move(title)), mWindowWidth(width), mWindowHeight(height) {
        mClock = std::make_unique<Clock>();
    }

    IGlfwApp::~IGlfwApp() {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    void IGlfwApp::Run() {
        if (!glfwInit())
            Panic("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, mWindowTitle.c_str(), None, None);
        if (!mWindow)
            Panic("Failed to create GLFW window");

        glfwMakeContextCurrent(mWindow);

        if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
            glfwTerminate();
            Panic("Failed to initialize OpenGL context");
        }

        CreateGLResources();

        glViewport(0, 0, mWindowWidth, mWindowHeight);
        glClearColor(0.f, 0.f, 0.f, 1.f);

        mClock->Start();
        while (!glfwWindowShouldClose(mWindow)) {
            mClock->Tick();
            {
                glfwPollEvents();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                Update();
                Render();

                glfwSwapBuffers(mWindow);
            }
            mClock->Update();
        }
        mClock->Stop();

        DestroyGLResources();
    }
}  // namespace GLTK
