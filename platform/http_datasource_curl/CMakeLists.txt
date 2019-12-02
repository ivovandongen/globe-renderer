include_vendor_pkg(curl)

add_module(http_datasource_curl)

target_link_libraries(http_datasource_curl
        PUBLIC
            core
            io
        PRIVATE
            curl
            logging
        )