# Get executable name
get_filename_component(EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${EXECUTABLE} PRIVATE
        renderer
        renderer_opengl3
        renderer_glfw
        glfw
        )

if (DO_CLANG_TIDY)
    set_target_properties(${EXECUTABLE} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()