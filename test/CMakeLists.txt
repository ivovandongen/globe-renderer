set(ALL_TESTS)

file(GLOB dirs "${CMAKE_CURRENT_SOURCE_DIR}/*")
foreach(dir ${dirs})
    if(IS_DIRECTORY ${dir})
        # Add the test module
        add_subdirectory(${dir})

        # Collect all test executables
        if(NOT ${dir} MATCHES "/common$")
            get_filename_component(TEST_DIR ${dir} NAME)
            list(APPEND ALL_TESTS "test_${TEST_DIR}")
        endif()
    endif()
endforeach()

# Add a custom command to execute all test executables
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run_all_tests.sh ${CMAKE_CURRENT_BINARY_DIR}/run_all_tests.sh COPYONLY)
add_custom_target(test ALL
        DEPENDS "${ALL_TESTS}"
        COMMAND ./run_all_tests.sh
)
