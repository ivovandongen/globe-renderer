#include <test.hpp>

#include <glbr/renderer/context.hpp>

using namespace glbr::renderer;

class ContextStub : public Context {
    void makeCurrent() const override { assert(false); };
    std::unique_ptr<VertexArray> createVertexArray() override { assert(false); };
    std::unique_ptr<IndexBuffer> createIndexBuffer(BufferHint, int) override { assert(false); };
    std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint, int) override { assert(false); };
    void clear(const ClearState &) override { assert(false); };
    void draw(const DrawState &, const SceneState &) override { assert(false); };
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
