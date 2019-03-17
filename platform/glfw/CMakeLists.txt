include_vendor_pkg(glfw)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(renderer_glfw
        ${SRC_DIR}/graphics_window_glfw.cpp
        )

target_link_libraries(renderer_glfw PUBLIC
        renderer
        renderer_opengl3
        glfw
        glad
        )

target_include_directories(renderer_glfw PUBLIC include)

if (DO_CLANG_TIDY)
    set_target_properties(renderer_glfw PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()