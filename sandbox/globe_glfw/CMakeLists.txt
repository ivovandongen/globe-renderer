# Get executable name
get_filename_component(EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${EXECUTABLE} PRIVATE
        core
        io
        logging
        renderer
        renderer_opengl3
        renderer_glfw
        scene
        )

file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "resources/*.*" "resources/**/*.*")
foreach (file ${files})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)
endforeach ()


if (DO_CLANG_TIDY)
    set_target_properties(${EXECUTABLE} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()