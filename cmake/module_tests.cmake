macro(ADD_TEST_MODULE MODULE_ON_TEST)

    get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    string(REPLACE " " "_" MODULE_NAME ${MODULE_NAME})
    set(MODULE_NAME test_${MODULE_NAME})

    message(STATUS "TESTS: Adding test module ${MODULE_NAME}")

    file(GLOB_RECURSE SRC_FILES
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

    include_vendor_pkg(googletest)

    set(COMMON_TEST_DIR ${CMAKE_SOURCE_DIR}/test/common)

    add_executable(${MODULE_NAME}
            ${COMMON_TEST_DIR}/test.hpp
            ${COMMON_TEST_DIR}/main.cpp

            ${SRC_FILES}
            )

    target_include_directories(${MODULE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${COMMON_TEST_DIR})

    target_link_libraries(${MODULE_NAME} PUBLIC gtest ${MODULE_ON_TEST})

    if (DO_CLANG_TIDY)
        set_target_properties(${MODULE_NAME} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
    endif ()

endmacro(ADD_TEST_MODULE)