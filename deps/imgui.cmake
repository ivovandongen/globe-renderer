include_guard_x()

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)

add_library(imgui STATIC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        )

target_include_directories(imgui
        PRIVATE ${IMGUI_DIR}
        )

target_include_directories(imgui
        SYSTEM INTERFACE ${IMGUI_DIR}
        )

if (APPLE)
    target_link_libraries(imgui INTERFACE "-framework CoreFoundation" "-framework Cocoa")
endif ()