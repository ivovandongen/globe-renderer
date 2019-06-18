#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>

#include <glbr/io/file.hpp>

#include <glm/vec3.hpp>

#include <array>

int main() {
    int width = 640, height = 480;

    using namespace glbr;
    using namespace glbr::renderer;

    logging::setLevel(logging::Level::DEBUG);

    SceneState sceneState(width, height);

    // Create the window
    glfw::GlfwGraphicsWindow window{width, height};

    // Set up the graphics device
    auto &device = opengl3::DeviceOpenGL3::instance();

    // Create the pipeline
    std::shared_ptr<Pipeline> pipeline = device.createPipeline(io::readFile("resources/triangle.vertex.glsl"),
                                                               io::readFile("resources/triangle.fragment.glsl"));

    // Create a vertex array
    std::shared_ptr<VertexArray> vertexArray = window.context().createVertexArray();
    vertexArray->bind();

    using Vertex = glm::vec3;
    std::array<Vertex, 4> vertices{
        Vertex{0.5f, 0.5f, 0.0f},    // top right
        Vertex{0.5f, -0.5f, 0.0f},   // bottom right
        Vertex{-0.5f, -0.5f, 0.0f},  // bottom left
        Vertex{-0.5f, 0.5f, 0.0f}    // top left
    };
    std::array<uint32_t, 6> indices{
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    // Add the vertices to the VertexBuffer
    std::shared_ptr<VertexBuffer> vertexBuffer =
        window.context().createVertexBuffer(BufferHint::StaticDraw, vertices.size() * sizeof(Vertex));
    vertexBuffer->bind();
    vertexBuffer->upload(vertices.data());

    // Set up the VertexAttributes
    vertexArray->add("aPos", {vertexBuffer, VertexBufferAttribute::Type::Float, 3, false, sizeof(Vertex), 0});

    // Add the indices to the IndexBuffer
    vertexArray->indexBuffer(window.context().createIndexBuffer(BufferHint::StaticDraw, indices.size()));
    vertexArray->indexBuffer()->bind();
    vertexArray->indexBuffer()->upload(indices.data());

    renderer::ClearState clearState{{0, 1, 1, 1}};

    // Add the color as a uniform
    pipeline->uniforms()["u_color"] = glm::vec4{1, 0, 0, 1};

    double counter = 1;
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
