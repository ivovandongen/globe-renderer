include_guard_x()

add_library(ctti INTERFACE)
target_include_directories(ctti SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/deps/ctti/include)