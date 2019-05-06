#include <test.hpp>

#include <glbr/io/file.hpp>

TEST(File, Read) {
    using namespace glbr::io;

    auto contents = readFile("resources/test.txt");
    ASSERT_EQ(contents, "TEST FILE\n");
}

TEST(File, ReadNonExisting) {
    using namespace glbr::io;

    ASSERT_THROW(readFile("resources/whatwhat.txt"), std::runtime_error);
}
