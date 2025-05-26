# cmake/SyncShaders.cmake

file(GLOB SHADER_FILES
        "${src}/*.glsl"
        "${src}/*.vert"
        "${src}/*.frag"
)
foreach(f IN LISTS SHADER_FILES)
    get_filename_component(fname "${f}" NAME)
    file(COPY "${f}" DESTINATION "${dst}")
endforeach()
