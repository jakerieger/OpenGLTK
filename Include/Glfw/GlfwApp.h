// Author: Jake Rieger
// Created: 9/25/2024.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Types.h"
#include "Clock.h"

namespace GLTK {
    /// @brief Provides an interface for implementing a GLFW-based application.
    ///
    /// The base class owns the window, frame timer (clock), and window properties
    /// while inheritors can manage additional resources like cameras as well as
    /// OpenGL objects in the dedicated virtual methods.
    ///
    /// For example usage, see
    /// https://github.com/jakerieger/ParticleSim/blob/64638194ccbd87ce6ab447fbc6c3a3d4797739fb/Source/main.cpp#L15
    class IGlfwApp {
    public:
        /// @brief Sets window properties and creates the clock. Width and height are optional
        /// parameters.
        explicit IGlfwApp(str title, int width = 800, int height = 600);

        /// @brief Cleans up GLFW resources.
        virtual ~IGlfwApp();

        /// @brief This is where all OpenGL objects should be created such as textures, shaders,
        /// vertex arrays, etc.
        virtual void CreateGLResources() = 0;

        /// @brief This is where all remaining OpenGL objects should be cleaned up.
        virtual void DestroyGLResources() = 0;

        /// @brief Application-loop update method. Delta time can be accessed via
        /// `mClock->GetDeltaTime()`.
        virtual void Update() = 0;

        /// @brief Application-loop render method. This is where you should do all your drawing.
        virtual void Render() = 0;

        /// @brief Initializes and enters the main application loop. If you're creating an instance
        /// of IGlfwApp, this is the only method you need to call to start and run the app.
        void Run();

    protected:
        GLFWwindow* mWindow = None;
        Unique<Clock> mClock;
        str mWindowTitle;
        int mWindowWidth;
        int mWindowHeight;
    };
}  // namespace GLTK