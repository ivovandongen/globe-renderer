include_vendor_pkg(glad)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(renderer_opengl3
        ${SRC_DIR}/context_opengl3.cpp
        ${SRC_DIR}/device_opengl3.cpp
        )

target_link_libraries(renderer_opengl3 PUBLIC
        glad
        )

target_include_directories(renderer_opengl3 PUBLIC include)

if (DO_CLANG_TIDY)
    set_target_properties(renderer_opengl3 PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()