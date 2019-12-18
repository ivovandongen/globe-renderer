include_guard_x()

add_library(tl-expected INTERFACE)
target_include_directories(tl-expected SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/deps/tl-expected/include)