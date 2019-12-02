#include <glbr/renderer/opengl3/textures/texture_unit_opengl3.hpp>

#include <test.hpp>

using namespace glbr::renderer;
using namespace glbr::renderer::opengl3;

TEST(TextureUnitOpenGL3, TextureBindingCaching) {
    // Mock basic gl functions;
    glGetError = []() { return 0u; };
    glDeleteTextures = [](GLsizei count, const GLuint *textures) {};

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
    textureUnit.clean();
    ASSERT_TRUE(textureUnitSet);
    ASSERT_TRUE(textureBound);

    // Set same texture
    textureUnitSet = false;
    textureBound = false;
    textureUnit.texture(a);
    textureUnit.clean();
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(textureBound);

    // Set same texture (through different object)
    textureUnit.texture(a1);
    textureUnit.clean();
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(textureBound);

    // Set different texture
    textureUnit.texture(b);
    textureUnit.clean();
    ASSERT_TRUE(textureUnitSet);
    ASSERT_TRUE(textureBound);
}

TEST(TextureUnitOpenGL3, TextureSamplerBindingCaching) {
    // Mock basic gl functions;
    glGetError = []() { return 0u; };
    glSamplerParameteri = [](GLuint sampler, GLenum pname, GLint param) {};
    glDeleteSamplers = [](GLsizei count, const GLuint *samplers) {};

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
    textureUnit.clean();
    ASSERT_TRUE(textureUnitSet);
    ASSERT_TRUE(samplerBound);

    // Set same texture
    textureUnitSet = false;
    samplerBound = false;
    textureUnit.sampler(a);
    textureUnit.clean();
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(samplerBound);

    // Set same texture (through different object)
    textureUnit.sampler(a1);
    textureUnit.clean();
    ASSERT_FALSE(textureUnitSet);
    ASSERT_FALSE(samplerBound);

    // Set different texture
    textureUnit.sampler(b);
    textureUnit.clean();
    ASSERT_TRUE(textureUnitSet);
    ASSERT_TRUE(samplerBound);
}