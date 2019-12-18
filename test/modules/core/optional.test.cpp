#include <glbr/core/optional.hpp>

#include <test.hpp>

TEST(Optional, Basic) {
    using namespace glbr::core;
    optional<std::string> empty;
    ASSERT_FALSE(empty);

    optional<std::string> not_empty{""};
    ASSERT_TRUE(not_empty);
}
