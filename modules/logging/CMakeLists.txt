add_module(logging)
include_vendor_pkg(spdlog)
target_link_libraries(logging PUBLIC spdlog)
