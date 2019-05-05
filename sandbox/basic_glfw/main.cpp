#include <renderer/glfw/graphics_window_glfw.hpp>
#include <renderer/opengl3/device_opengl3.hpp>

#include <io/file.hpp>

#include <array>

int main() {
    int width = 640, height = 480;

    using namespace renderer;

    // Create the window
    glfw::GlfwGraphicsWindow window{width, height};

    // Set up the graphics device
    auto &device = opengl3::DeviceOpenGL3::instance();

    // Create the pipeline
    auto pipeline = device.createPipeline(io::readFile("resources/triangle.vertex.glsl"),
                                          io::readFile("resources/triangle.fragment.glsl"));

    pipeline->bind();

    // Create a vertex array
    auto vertexArray = window.context().createVertexArray();
    vertexArray->bind();

    std::array<float, 12> vertices{
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f   // top left
    };
    std::array<unsigned int, 6> indices{
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    // Add the vertices to the VertexBuffer
    auto vertexBuffer = window.context().createVertexBuffer(BufferHint::StaticDraw, vertices.size() * sizeof(float));
    vertexBuffer->bind();
    vertexBuffer->upload(vertices.data());

    // Set up the VertexAttributes
    vertexArray->add({VertexAttribute::Type::Float, 3, false, 3 * sizeof(float), 0});

    // Add the indices to the IndexBuffer
    auto indexBuffer = window.context().createIndexBuffer(BufferHint::StaticDraw, indices.size() * sizeof(float));
    indexBuffer->bind();
    indexBuffer->upload(indices.data());
    vertexArray->indexBuffer(std::move(indexBuffer));

    renderer::ClearState clearState{{0, 1, 1, 1}};

    // Add the color as a uniform
    pipeline->setUniform("u_color", glm::vec4{1, 0, 0, 1});

    int counter = 1;
    int step = 1;

    // Render function
    auto renderFn = [&](renderer::Context &context) {
        // Clear the scene
        clearState.color = {1. - (counter / 100.), 0, 1. - (counter / 100.), 1};
        context.clear(clearState);

        // Draw the rectangle
        context.draw({{}, *pipeline, *vertexArray});
    };

    // Update function
    auto updateFn = [&]() {
        if (counter >= 100) {
            step = -1;
        } else if (counter <= 0) {
            step = 1;
        }
        counter += step;
    };

    // Runloop
    window.run(renderFn, updateFn, 60);

    glfwTerminate();
}
