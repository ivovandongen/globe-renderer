include_vendor_pkg("glfw")
include_vendor_pkg("glad")

add_executable(sandbox
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(sandbox PRIVATE
        renderer
        glad
        glfw
        )

if (DO_CLANG_TIDY)
    set_target_properties(sandbox PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()