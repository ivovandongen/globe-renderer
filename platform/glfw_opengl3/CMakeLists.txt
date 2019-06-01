include_vendor_pkg(glfw)

add_module(renderer_glfw)

target_link_libraries(renderer_glfw
        PUBLIC
            renderer
        PRIVATE
            glfw
            glad
            renderer_opengl3
        )