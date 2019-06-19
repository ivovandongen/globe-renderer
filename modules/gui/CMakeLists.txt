include_vendor_pkg(imgui)

#temporary
include_vendor_pkg(glad)

add_module(gui)

target_link_libraries(gui PUBLIC
        core
        input
        imgui
        renderer
        scene
        )