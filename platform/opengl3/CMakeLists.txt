include_vendor_pkg(glad)

file(GLOB_RECURSE HEADER_FILES
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(renderer_opengl3
        ${HEADER_FILES}

        ${SRC_DIR}/context_opengl3.cpp
        ${SRC_DIR}/device_opengl3.cpp
        ${SRC_DIR}/pipeline_opengl3.cpp
        ${SRC_DIR}/buffers/buffer_opengl3.cpp
        ${SRC_DIR}/buffers/index_buffer_opengl3.cpp
        ${SRC_DIR}/buffers/vertex_buffer_opengl3.cpp
        ${SRC_DIR}/vertex_array/vertex_array_opengl3.cpp
        )

target_link_libraries(renderer_opengl3 PUBLIC
        glad
        core
        renderer
        )

target_include_directories(renderer_opengl3
        PUBLIC
        include
        PRIVATE
        src
        )

if (DO_CLANG_TIDY)
    set_target_properties(renderer_opengl3 PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()