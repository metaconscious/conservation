file(GLOB SHADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag
)

set(SHADERS_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")
add_custom_command(
        OUTPUT "${SHADERS_DEST_DIR}/.stamp"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADERS_DEST_DIR}"
        COMMAND ${CMAKE_COMMAND} -Dsrc="${CMAKE_CURRENT_SOURCE_DIR}/shaders" -Ddst="${SHADERS_DEST_DIR}" -P "${CMAKE_SOURCE_DIR}/cmake/SyncShaders.cmake"
        COMMAND ${CMAKE_COMMAND} -E touch "${SHADERS_DEST_DIR}/.stamp"
        DEPENDS ${SHADERS}
        COMMENT "Synchronizing shaders to binary dir"
        VERBATIM
)
add_custom_target(sync_shaders ALL DEPENDS "${SHADERS_DEST_DIR}/.stamp")

add_executable(conservation src/main.cpp)
target_link_libraries(conservation PRIVATE OpenGL::GL glfw glad glm::glm)