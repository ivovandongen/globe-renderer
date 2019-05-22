#include <test.hpp>

#include <glbr/renderer/vertex_buffer_attributes/vertex_buffer_attribute_bindings.hpp>

namespace {

template <class T>
class ConstTest {
public:
    void operator()(T& binding) { FAIL(); }
    void operator()(const T& binding) { SUCCEED(); }
};

}  // namespace

TEST(VertexAttributeBindings, ConstIterable) {
    using namespace glbr::renderer;

    std::shared_ptr<VertexBuffer> buffer;

    VertexBufferAttributeBindings bindings{
        {"my_attribute", VertexBufferAttribute{buffer, VertexBufferAttribute::Type::Float, 1, false, 1, 1}}};

    ConstTest<VertexBufferAttribute> constTest;
    bool iterated = false;
    for (auto& binding : bindings) {
        iterated = true;
        constTest(binding.second);
    }

    ASSERT_TRUE(iterated);
}

TEST(VertexAttributeBindings, ConstAt) {
    using namespace glbr::renderer;

    std::shared_ptr<VertexBuffer> buffer;

    VertexBufferAttributeBindings bindings{
        {"my_attribute", VertexBufferAttribute{buffer, VertexBufferAttribute::Type::Float, 1, false, 1, 1}}};

    ConstTest<VertexBufferAttribute> constTest;
    constTest(bindings.at("my_attribute"));
    ASSERT_EQ(bindings.at("my_attribute").type(), VertexBufferAttribute::Type::Float);
}

TEST(VertexAttributeBindings, SubscriptOperator) {
    using namespace glbr::renderer;

    std::shared_ptr<VertexBuffer> buffer;

    VertexBufferAttributeBindings bindings;

    bindings["my_attribute"] = VertexBufferAttribute{buffer, VertexBufferAttribute::Type::Float, 2, false, 1, 1};
    ASSERT_EQ(bindings["my_attribute"].components(), 2);
}

TEST(VertexAttributeBindings, ConstSubscriptOperator) {
    using namespace glbr::renderer;

    std::shared_ptr<VertexBuffer> buffer;

    VertexBufferAttributeBindings bindings{
        {"my_attribute", VertexBufferAttribute{buffer, VertexBufferAttribute::Type::Float, 1, false, 1, 1}}};

    ConstTest<VertexBufferAttribute> constTest;
    const auto& attr = bindings["my_attribute"];
    constTest(attr);
    ASSERT_EQ(attr.type(), VertexBufferAttribute::Type::Float);
}
