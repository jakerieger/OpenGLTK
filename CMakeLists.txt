cmake_minimum_required(VERSION 3.14)
project(OpenGLTK)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(ThirdParty/ThirdPartySources.cmake)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
)

set(SOURCES
        Source/Camera.cpp
        Source/Clock.cpp
        Source/OpenGLTK.cpp
        Source/Shader.cpp
        Source/Glfw/GlfwApp.cpp
)

set(INCLUDES
        Include/Buffer.h
        Include/Camera.h
        Include/Clock.h
        Include/IO.h
        Include/OpenGLTK.h
        Include/Primitives.h
        Include/Shader.h
        Include/Texture.h
        Include/Types.h
        Include/VertexArray.h
)

add_library(OpenGLTK STATIC
        ${THIRD_PARTY_SRCS}
        ${INCLUDES}
        ${SOURCES}
)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(OpenGLTK PRIVATE
        glfw
        glm::glm-header-only
)