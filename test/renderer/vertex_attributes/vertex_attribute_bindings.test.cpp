#include <test.hpp>

#include <glbr/renderer/vertex_attributes/vertex_attribute_bindings.hpp>

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

    VertexAttributeBindings bindings{{"my_attribute", VertexAttribute{VertexAttribute::Type::Float, 1, false, 1, 1}}};

    ConstTest<VertexAttribute> constTest;
    bool iterated = false;
    for (auto& binding : bindings) {
        iterated = true;
        constTest(binding.second);
    }

    ASSERT_TRUE(iterated);
}

TEST(VertexAttributeBindings, ConstAt) {
    using namespace glbr::renderer;

    VertexAttributeBindings bindings{{"my_attribute", VertexAttribute{VertexAttribute::Type::Float, 1, false, 1, 1}}};

    ConstTest<VertexAttribute> constTest;
    constTest(bindings.at("my_attribute"));
    ASSERT_EQ(bindings.at("my_attribute").type(), VertexAttribute::Type::Float);
}

TEST(VertexAttributeBindings, SubscriptOperator) {
    using namespace glbr::renderer;

    VertexAttributeBindings bindings;

    bindings["my_attribute"] = VertexAttribute{VertexAttribute::Type::Float, 2, false, 1, 1};
    ASSERT_EQ(bindings["my_attribute"].components(), 2);
}

TEST(VertexAttributeBindings, ConstSubscriptOperator) {
    using namespace glbr::renderer;

    VertexAttributeBindings bindings{{"my_attribute", VertexAttribute{VertexAttribute::Type::Float, 1, false, 1, 1}}};

    ConstTest<VertexAttribute> constTest;
    const auto& attr = bindings["my_attribute"];
    constTest(attr);
    ASSERT_EQ(attr.type(), VertexAttribute::Type::Float);
}
