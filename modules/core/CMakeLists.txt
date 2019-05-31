add_module(core)

include_vendor_pkg(ctti)
include_vendor_pkg(glm)
include_vendor_pkg(stb)
include_vendor_pkg(tl-optional)
include_vendor_pkg(variant)

target_link_libraries(core
        PUBLIC
        ctti
        glm
        tl-optional
        variant
        logging

        PRIVATE
        stb
        )