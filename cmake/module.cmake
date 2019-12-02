macro(ADD_MODULE MODULE_NAME)

    message(STATUS "MODULES: Adding module ${MODULE_NAME}")

    file(GLOB_RECURSE HEADER_FILES
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

    file(GLOB_RECURSE SRC_FILES
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

    set(${MODULE_NAME}_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)

    if (NOT "${SRC_FILES}" STREQUAL "")

        add_library(${MODULE_NAME} STATIC
                ${HEADER_FILES}

                ${SRC_FILES}
                )

        target_include_directories(${MODULE_NAME} PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>
                )

        if (DO_CLANG_TIDY)
            set_target_properties(${MODULE_NAME} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
        endif ()

    else()
        add_library(${MODULE_NAME} INTERFACE)

        target_include_directories(${MODULE_NAME} INTERFACE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>
                )
    endif()

endmacro(ADD_MODULE)