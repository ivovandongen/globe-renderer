include_vendor_pkg(glad)

add_module(renderer_opengl3)

target_link_libraries(renderer_opengl3 PUBLIC
        glad
        core
        renderer)