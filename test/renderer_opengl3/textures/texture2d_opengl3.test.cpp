#include <glbr/renderer/opengl3/textures/texture2d_opengl3.hpp>

#include <test.hpp>

using namespace glbr::renderer;
using namespace glbr::renderer::opengl3;

TEST(Texture2DOpenGL3, Compare) {
    // Mock basic gl functions;
    glGetError = []() { return 0u; };
    glDeleteTextures = [](GLsizei count, const GLuint *textures) {};

    Texture2DDescription description{1, 1, TextureFormat::Depth24, false};
    TextureTarget target = TextureTarget::Texture2D;

    glGenTextures = [](GLsizei count, GLuint *textures) { textures[0] = 1; };
    Texture2DOpenGL3 a(description, target);
    Texture2DOpenGL3 a1(description, target);

    glGenTextures = [](GLsizei count, GLuint *textures) { textures[0] = 2; };
    Texture2DOpenGL3 b(description, target);

    // Basics
    ASSERT_EQ(a, a);
    ASSERT_NE(a, b);

    // Same underlying gl Object
    ASSERT_EQ(a, a1);
}