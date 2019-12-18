#include <glbr/renderer/opengl3/context/context_opengl3.hpp>

#include <glbr/renderer/opengl3/textures/texture_unit_opengl3.hpp>

#include <test.hpp>

using namespace glbr::core;
using namespace glbr::input;
using namespace glbr::renderer;
using namespace glbr::renderer::opengl3;

class MockGraphicsWindow : public GraphicsWindow {
public:
    MOCK_METHOD(std::unique_ptr<EventHandlerRegistration>, registerHandler, (const EventHandlingFN &fn), (override));
    MOCK_METHOD(KeyState, keyState, (KeyCode), (const override));
    MOCK_METHOD(KeyState, mouseButtonState, (MouseButtonCode), (const override));
    MOCK_METHOD(Position, mousePosition, (), (const override));
    MOCK_METHOD(void, makeContextCurrent, (), (const override));
    MOCK_METHOD(Context &, context, (), (const override));
    MOCK_METHOD(Size2D<int>, size, (), (const override));
    MOCK_METHOD(float, pixelRatio, (), (const override));
    MOCK_METHOD(void, run, (const RenderFN &), (override));
    MOCK_METHOD(void, run, (const RenderFN &, const UpdateFN &, double), (override));
    MOCK_METHOD(void, close, (), (override));
};

static void mockGL() {
    // Mock basic gl functions;
    glGetError = []() { return 0u; };
    glDeleteTextures = [](GLsizei count, const GLuint *textures) {};
    glSamplerParameteri = [](GLuint sampler, GLenum pname, GLint param) {};
    glDeleteSamplers = [](GLsizei count, const GLuint *samplers) {};
    glGetIntegerv = [](GLenum pname, GLint *data) {
        switch (pname) {
            case GL_MAX_TEXTURE_IMAGE_UNITS:
                *data = 16u;
                break;
            default:
                assert(false);
        }
    };
}

TEST(ContextOpenGL3, ActiveTextureUnit) {
    mockGL();

    static GLenum activeTexture = std::numeric_limits<GLenum>::max();
    static uint callCount = 0;
    glActiveTexture = [](GLenum texture) {
        activeTexture = texture;
        callCount++;
    };

    TextureUnitOpenGL3 unit0{0};
    TextureUnitOpenGL3 unit1{1};

    MockGraphicsWindow window;
    ContextOpenGL3 context{window};

    // Set the active texture unit
    context.activeTextureUnit(unit0);
    ASSERT_EQ(activeTexture, GL_TEXTURE0);
    ASSERT_EQ(callCount, 1);

    // Set the same again, should not call through to opengl
    context.activeTextureUnit(unit0);
    ASSERT_EQ(activeTexture, GL_TEXTURE0);
    ASSERT_EQ(callCount, 1);

    // Set a new one
    context.activeTextureUnit(unit1);
    ASSERT_EQ(activeTexture, GL_TEXTURE1);
    ASSERT_EQ(callCount, 2);

    // Set the same again, should not call through to opengl
    context.activeTextureUnit(unit1);
    ASSERT_EQ(activeTexture, GL_TEXTURE1);
    ASSERT_EQ(callCount, 2);
}