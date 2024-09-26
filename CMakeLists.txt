cmake_minimum_required(VERSION 3.14)
project(OpenGLTK)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(ThirdParty/ThirdPartySources.cmake)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
)

set(SOURCES
        Source/Types.h
        Source/IO.h
        Source/OpenGLTK.cpp
        Source/OpenGLTK.h
        Source/Shader.cpp
        Source/Shader.h
        Source/Texture.h
        Source/VertexArray.h
        Source/Camera.cpp
        Source/Camera.h
        Source/Buffer.h
        Source/Clock.cpp
        Source/Clock.h
        Source/Glfw/GlfwApp.cpp
        Source/Glfw/GlfwApp.h
        Source/Primitives.h
)

add_library(OpenGLTK STATIC
        ${THIRD_PARTY_SRCS}
        ${SOURCES}
)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(OpenGLTK PRIVATE
        glfw
        glm::glm-header-only
)