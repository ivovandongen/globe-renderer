add_subdirectory(logging)
add_subdirectory(core)
add_subdirectory(io)
add_subdirectory(input)
add_subdirectory(renderer)
add_subdirectory(scene)
add_subdirectory(gui)

if (ENABLE_OPENGL)
    add_subdirectory(renderer_opengl3)
endif ()