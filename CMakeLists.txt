cmake_minimum_required(VERSION 3.29)
project(OpenGLTK)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(ThirdParty/ThirdPartySources.cmake)

include_directories(
        ${CMAKE_SOURCE_DIR}/Source
        ${CMAKE_SOURCE_DIR}/ThirdParty
)

set(SOURCES
        Source/Types.h
        Source/IO.h
        Source/OpenGLTK.cpp
        Source/OpenGLTK.h
        Source/Shader.cpp
        Source/Shader.h
        Source/TextureLoader.h
        Testbed/main.cpp
        Source/Vertex.h
        Source/Camera.cpp
        Source/Camera.h
)

add_library(OpenGLTK STATIC
        ${THIRD_PARTY_SRCS}
        ${SOURCES}
)

find_package(glm CONFIG REQUIRED)

target_link_libraries(OpenGLTK PRIVATE
        glm::glm-header-only
)

add_subdirectory(Testbed)