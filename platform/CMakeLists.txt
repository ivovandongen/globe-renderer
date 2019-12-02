if (ENABLE_OPENGL)
    add_subdirectory(glfw_opengl3)
endif ()

if (ENABLE_CURL)
    add_subdirectory(http_datasource_curl)
endif ()