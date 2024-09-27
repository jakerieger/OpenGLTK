// Author: Jake Rieger
// Created: 9/25/2024.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Types.h"
#include "Clock.h"

namespace GLTK {
    class IGlfwApp {
    public:
        explicit IGlfwApp(str title, int width = 800, int height = 600);
        virtual ~IGlfwApp();
        virtual void CreateGLResources()  = 0;
        virtual void DestroyGLResources() = 0;
        virtual void Update()             = 0;
        virtual void Render()             = 0;
        void Run();

    protected:
        GLFWwindow* mWindow = None;
        Unique<Clock> mClock;
        str mWindowTitle;
        int mWindowWidth;
        int mWindowHeight;
    };
}  // namespace GLTK