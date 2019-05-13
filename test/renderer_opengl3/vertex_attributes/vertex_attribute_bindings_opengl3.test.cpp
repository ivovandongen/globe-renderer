#include <test.hpp>

#include <glbr/renderer/opengl3/vertex_buffer_attributes/vertex_buffer_attribute_bindings_opengl3.hpp>

TEST(VertexAttributeBindingsOpenGL3, DirtyChecking) {
    using namespace glbr::renderer;
    using namespace glbr::renderer::opengl3;

    VertexBufferAttributeBindingsOpenGL3 bindings{
        {"my_attribute", {VertexBufferAttribute::Type::Float, 1, false, 1, 1}}};
    ASSERT_TRUE(bindings.dirty());

    bindings = {};
    ASSERT_FALSE(bindings.dirty());

    bindings["my_attribute"] = {VertexBufferAttribute::Type::Float, 1, false, 1, 1};
    ASSERT_TRUE(bindings.dirty());
}
