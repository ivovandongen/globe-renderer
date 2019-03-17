add_library(renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/shader_program.cpp
        )

if (DO_CLANG_TIDY)
    set_target_properties(renderer PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()