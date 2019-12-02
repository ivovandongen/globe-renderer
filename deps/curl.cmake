include_guard_x()

option(BUILD_CURL_EXE "We don't need the executable" OFF)
option(BUILD_SHARED_LIBS "We want static libs" OFF)
option(HTTP_ONLY "We only need HTTP" ON)
option(BUILD_TESTING "Let's assume the code has been tested" OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/curl ${CMAKE_BINARY_DIR}/curl EXCLUDE_FROM_ALL)

set_target_properties(libcurl PROPERTIES CXX_CLANG_TIDY "")
set_target_properties(libcurl PROPERTIES C_CLANG_TIDY "")

# Wrap the target into a new target to be able to control the interface
add_library(curl STATIC ${CMAKE_SOURCE_DIR}/deps/dummy.cpp)
target_include_directories(curl SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/deps/curl/include)
target_link_libraries(curl PUBLIC libcurl)
