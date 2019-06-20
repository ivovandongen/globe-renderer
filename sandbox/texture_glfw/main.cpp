#include <glbr/core/image.hpp>
#include <glbr/io/file.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture_sampler_opengl3.hpp>
#include <glbr/renderer/textures/texture2d.hpp>

#include <glad/glad.h>

#include <array>

GLenum toGLFormat(int channels, bool gammaCorrected = false) {
    switch (channels) {
        case 1:
            return GL_RED;
        case 3:
            return gammaCorrected ? GL_SRGB : GL_RGB;
        case 4:
            return gammaCorrected ? GL_SRGB_ALPHA : GL_RGBA;
        default:
            return gammaCorrected ? GL_SRGB : GL_RGB;
            ;
    }
}

int main() {
    int width = 640, height = 480;

    using namespace glbr;
    using namespace glbr::core;
    using namespace glbr::renderer;

    logging::setLevel(logging::Level::DEBUG);

    SceneState sceneState(width, height);

    Image kitty{"resources/kitty.png"};
    Image kittyRev{"resources/kitty.png", false};

    // Create the window
    glfw::GlfwGraphicsWindow window{width, height};

    // Set up the graphics device
    auto &device = opengl3::DeviceOpenGL3::instance();

    // Create the pipeline
    std::shared_ptr<Pipeline> pipeline =
        device.createPipeline(io::readFile("resources/vertex.glsl"), io::readFile("resources/fragment.glsl"));

    // Create a vertex array
    std::shared_ptr<VertexArray> vertexArray = window.context().createVertexArray();
    vertexArray->bind();

    std::array<float, 4 * 5> vertices{
        0.5f,  0.5f,  0.0f, 2., 2.,  // top right
        0.5f,  -0.5f, 0.0f, 2., .0,  // bottom right
        -0.5f, -0.5f, 0.0f, .0, .0,  // bottom left
        -0.5f, 0.5f,  0.0f, .0, 2.   // top left
    };
    std::array<unsigned int, 6> indices{
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    // Add the vertices to the VertexBuffer
    std::shared_ptr<VertexBuffer> vertexBuffer =
        window.context().createVertexBuffer(BufferHint::StaticDraw, vertices.size() * sizeof(float));
    vertexBuffer->bind();
    vertexBuffer->upload(vertices.data());

    // Set up the VertexAttributes
    vertexArray->add("aPos", {vertexBuffer, VertexBufferAttribute::Type::Float, 3, false, 5 * sizeof(float), 0});
    vertexArray->add(
        "aTex", {vertexBuffer, VertexBufferAttribute::Type::Float, 2, false, 5 * sizeof(float), 3 * sizeof(float)});

    // Add the indices to the IndexBuffer
    auto indexBuffer =
        window.context().createIndexBuffer(IndexBufferType::U_INT, BufferHint::StaticDraw, indices.size());
    indexBuffer->bind();
    indexBuffer->upload(indices.data());
    vertexArray->indexBuffer(std::move(indexBuffer));

    // Create a Texture
    window.context().textureUnits()[0].texture(device.createTexture2D(kitty, true));
    window.context().textureUnits()[0].sampler(
        device.createTextureSampler(TextureMinificationFilter::NEAREST, TextureMagnificationFilter::NEAREST,
                                    TextureWrap::MIRRORED_REPEAT, TextureWrap::MIRRORED_REPEAT));
    pipeline->uniforms()["texture1"] = 0;

    // Create another texture in the next texture unit
    window.context().textureUnits()[1].texture(device.createTexture2D(kittyRev, true));
    window.context().textureUnits()[1].sampler(
        device.createTextureSampler(TextureMinificationFilter::NEAREST, TextureMagnificationFilter::NEAREST,
                                    TextureWrap::MIRRORED_REPEAT, TextureWrap::MIRRORED_REPEAT));
    pipeline->uniforms()["texture2"] = 1;

    renderer::ClearState clearState{ClearBuffers::COLOR, {0, 1, 1, 1}};

    float counter = 1;
    int step = 1;

    // Render function
    auto renderFn = [&](renderer::Context &context) {
        // Clear the scene
        clearState.color = {1. - (counter / 100.), 0, 1. - (counter / 100.), 1};
        context.clear(clearState);

        // Draw the rectangle
        context.draw(core::geometry::PrimitiveType::TRIANGLES, {{}, pipeline, vertexArray}, sceneState);
    };

    // Update function
    auto updateFn = [&](auto interval) {
        if (counter >= 100) {
            step = -1;
        } else if (counter <= 0) {
            step = 1;
        }
        counter += step * interval.count() / 16666666;
    };

    // Runloop
    window.run(renderFn, updateFn, 60);
}
