if (ENABLE_CURL)
    add_test_module(http_datasource_curl)
    target_link_libraries(test_http_datasource_curl PUBLIC core)
endif ()