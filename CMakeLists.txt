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
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/OpenGLTK.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Glfw/GlfwApp.cpp
)

set(INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Buffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Clock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/IO.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/OpenGLTK.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Primitives.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/VertexArray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/Glfw/GlfwApp.h
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

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Includes.cmake)