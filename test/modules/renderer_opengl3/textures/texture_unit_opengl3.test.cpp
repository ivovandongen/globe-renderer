#include <glbr/renderer/opengl3/textures/texture_unit_opengl3.hpp>

#include <glbr/renderer/graphics_window.hpp>
#include <glbr/renderer/opengl3/context/context_opengl3.hpp>

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

class MockGLContext : public ContextOpenGL3 {
public:
    explicit MockGLContext(GraphicsWindow &win) : ContextOpenGL3(win) {}
};

static void mockGL() {
    // Mock basic gl functions;
    glGetError = []() { return 0u; };
    glDeleteTextures = [](GLsizei count, const GLuint *textures) {};
    glSamplerParameteri = [](GLuint sampler, GLenum pname, GLint param) {};
    glDeleteSamplers = [](GLsizei count, const GLuint *samplers) {};
    glGetIntegerv= [](GLenum pname, GLint* data) {
        switch (pname) {
            case GL_MAX_TEXTURE_IMAGE_UNITS:
                *data = 16u;
                break;
            default:
                assert(false);
        }
    };
}

TEST(TextureUnitOpenGL3, TextureBindingCaching) {
    mockGL();
    MockGraphicsWindow window;
    MockGLContext context{window};

    Texture2DDescription description{1, 1, TextureFormat::Depth24, false};
    TextureTarget target = TextureTarget::Texture2D;

    glGenTextures = [](GLsizei count, GLuint *textures) { textures[0] = 1; };
    auto a = std::make_shared<Texture2DOpenGL3>(description, target);
    auto a1 = std::make_shared<Texture2DOpenGL3>(description, target);

    glGenTextures = [](GLsizei count, GLuint *textures) { textures[0] = 2; };
    auto b = std::make_shared<Texture2DOpenGL3>(description, target);

    TextureUnitOpenGL3 textureUnit{0};

    // Checks
    static bool textureUnitSet = false;
    glActiveTexture = [](GLenum texture) { textureUnitSet = true; };
    static bool textureBound = false;
    glBindTexture = [](GLenum target, GLuint texture) { textureBound = true; };

    // Set initial texture
    textureUnit.texture(a);
    textureUnit.clean(context);
    ASSERT_TRUE(textureUnitSet);
    ASSERT_TRUE(textureBound);

    // Set same texture
    textureUnitSet = false;
    textureBound = false;
    textureUnit.texture(a);
    textureUnit.clean(context);
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(textureBound);

    // Set same texture (through different object)
    textureUnit.texture(a1);
    textureUnit.clean(context);
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(textureBound);

    // Set different texture
    textureUnit.texture(b);
    textureUnit.clean(context);
    ASSERT_FALSE(textureUnitSet);
    ASSERT_TRUE(textureBound);
}

TEST(TextureUnitOpenGL3, TextureSamplerBindingCaching) {
    mockGL();
    MockGraphicsWindow window;
    MockGLContext context{window};

    glGenSamplers = [](GLsizei count, GLuint *samplers) { samplers[0] = 1; };
    auto a = std::make_shared<TextureSamplerOpenGL3>(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);
    auto a1 = std::make_shared<TextureSamplerOpenGL3>(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);

    glGenSamplers = [](GLsizei count, GLuint *samplers) { samplers[0] = 2; };
    auto b = std::make_shared<TextureSamplerOpenGL3>(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);

    TextureUnitOpenGL3 textureUnit{0};

    // Checks
    static bool textureUnitSet = false;
    glActiveTexture = [](GLenum texture) { textureUnitSet = true; };
    static bool samplerBound = false;
    glBindSampler = [](GLenum target, GLuint sampler) { samplerBound = true; };

    // Set initial texture
    textureUnit.sampler(a);
    textureUnit.clean(context);
    ASSERT_TRUE(textureUnitSet);
    ASSERT_TRUE(samplerBound);

    // Set same texture
    textureUnitSet = false;
    samplerBound = false;
    textureUnit.sampler(a);
    textureUnit.clean(context);
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(samplerBound);

    // Set same texture (through different object)
    textureUnit.sampler(a1);
    textureUnit.clean(context);
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(samplerBound);

    // Set different texture
    textureUnit.sampler(b);
    textureUnit.clean(context);
    ASSERT_FALSE(textureUnitSet);
    ASSERT_TRUE(samplerBound);
}