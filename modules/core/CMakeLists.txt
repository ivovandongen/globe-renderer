add_module(core)

include_vendor_pkg(glm)
include_vendor_pkg(tl-optional)

target_link_libraries(core INTERFACE
        glm
        tl-optional
        )