add_subdirectory(logging)
add_subdirectory(core)
add_subdirectory(io)
add_subdirectory(renderer)

if (ENABLE_OPENGL)
    add_subdirectory(renderer_opengl3)
endif ()