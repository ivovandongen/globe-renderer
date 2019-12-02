#include <glbr/renderer/opengl3/textures/texture_sampler_opengl3.hpp>

#include <test.hpp>

using namespace glbr::renderer;
using namespace glbr::renderer::opengl3;

TEST(TextureSamplerOpenGL3, Compare) {
    // Mock basic gl functions;
    glGetError = []() { return 0u; };
    glSamplerParameteri = [](GLuint sampler, GLenum pname, GLint param) {};
    glDeleteSamplers = [](GLsizei count, const GLuint *samplers) {};
    glBindSampler = [](GLuint unit, GLuint sampler) {};

    glGenSamplers = [](GLsizei count, GLuint *samplers) { samplers[0] = 1; };
    TextureSamplerOpenGL3 a(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);
    TextureSamplerOpenGL3 a1(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);

    glGenSamplers = [](GLsizei count, GLuint *samplers) { samplers[0] = 2; };
    TextureSamplerOpenGL3 b(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);

    // Basics
    ASSERT_EQ(a, a);
    ASSERT_NE(a, b);

    // Same underlying gl Object
    ASSERT_EQ(a, a1);
}