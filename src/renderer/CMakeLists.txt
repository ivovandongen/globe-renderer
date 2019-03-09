include_vendor_pkg(glad)

add_library(renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/shader_program.cpp
        )

target_link_libraries(renderer PUBLIC
        glfw
        glad
        )

if (DO_CLANG_TIDY)
    set_target_properties(renderer PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()