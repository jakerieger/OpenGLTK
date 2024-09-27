set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(INCLUDE_DIR ${CMAKE_BINARY_DIR}/include)

add_custom_command(
        OUTPUT ${INCLUDE_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${INCLUDE_DIR}/OpenGLTK
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${HEADER_DIR} ${INCLUDE_DIR}/OpenGLTK
        COMMENT "Copying header files to ${INCLUDE_DIR}, retaining directory structure"
)

add_custom_target(copy_headers ALL DEPENDS ${INCLUDE_DIR})