#include <test.hpp>

#include <glbr/renderer/context.hpp>

using namespace glbr::renderer;
using namespace glbr::core::geometry;

struct ContextStub : public Context {
    void makeCurrent() const override { assert(false); };
    Device &device() override { assert(false); }
    const Device &device() const override { assert(false); }
    std::unique_ptr<VertexArray> createVertexArray() const override { assert(false); };
    std::unique_ptr<IndexBuffer> createIndexBuffer(IndexBufferType, BufferHint, uint32_t) const override {
        assert(false);
    };
    std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint, int) const override { assert(false); };
    void clear(const ClearState &) override { assert(false); };
    void draw(PrimitiveType, const DrawState &, const SceneState &, uint32_t) override { assert(false); };
    TextureUnits &textureUnits() override { assert(false); }
};

TEST(Context, ResizeListener) {
    bool callbackFired = false;

    ContextStub stub;
    stub.setOnResizeListener([&](float width, float height) {
        callbackFired = true;
        ASSERT_EQ(width, 100);
        ASSERT_EQ(height, 200);
    });

    stub.viewport(100, 200);

    ASSERT_TRUE(callbackFired);
}
