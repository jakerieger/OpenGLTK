cmake_minimum_required(VERSION 3.14)
project(OpenGLTK)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Testbed)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCES
        ${SRC_DIR}/main.cpp
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Source
        ${CMAKE_SOURCE_DIR}/ThirdParty
)

add_executable(Testbed
        ${THIRD_PARTY_SRCS}
        ${SOURCES}
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Testbed PRIVATE
        glfw
        OpenGLTK
)

add_custom_command(TARGET Testbed PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets)