#include <test.hpp>

#include <glbr/core/geometry/mesh.hpp>

#include <array>

using namespace glbr::core;
using namespace glbr::core::geometry;

TEST(Mesh, Basic) {
    struct Vertex {
        std::array<float, 3> position;
        std::array<unsigned char, 2> color;
    };
    using Index = std::array<float, 3>;

    auto mesh = Mesh::Create<Vertex, Index>({{"position", VertexAttributeType::Float, 3},
                                             {"other", VertexAttributeType::UnsignedByte, 2, offsetof(Vertex, color)}});

    ASSERT_EQ(mesh->windingOrder(), WindingOrder::COUNTER_CLOCK_WISE);
    ASSERT_EQ(mesh->primitiveType(), PrimitiveType::Triangles);
    ASSERT_EQ(mesh->vertexAttributes().size(), 2);
    ASSERT_EQ(mesh->vertexAttributes()[0].name(), "position");
    ASSERT_EQ(mesh->vertexAttributes()[0].type(), VertexAttributeType::Float);
    ASSERT_EQ(mesh->vertexAttributes()[0].size(), 3 * sizeof(float));
    ASSERT_EQ(mesh->vertexAttributes()[1].name(), "other");
    ASSERT_EQ(mesh->vertexAttributes()[1].type(), VertexAttributeType::UnsignedByte);
    ASSERT_EQ(mesh->vertexAttributes()[1].size(), 2 * sizeof(unsigned char));
}
