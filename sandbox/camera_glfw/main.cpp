#include <glbr/io/file.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <array>

int main() {
    int width = 640, height = 480;

    using namespace glbr;
    using namespace glbr::renderer;

    // Create the window
    glfw::GlfwGraphicsWindow window{width, height};

    // Set up the graphics device
    auto &device = opengl3::DeviceOpenGL3::instance();

    SceneState sceneState(width, height);
    sceneState.camera().position({0, 0, 3});

    // Create the pipeline
    auto pipeline =
        device.createPipeline(io::readFile("resources/vertex.glsl"), io::readFile("resources/fragment.glsl"));

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
    vertexArray->add("aPos", {VertexAttribute::Type::Float, 3, false, 3 * sizeof(float), 0});

    // Add the indices to the IndexBuffer
    auto indexBuffer = window.context().createIndexBuffer(BufferHint::StaticDraw, indices.size() * sizeof(float));
    indexBuffer->bind();
    indexBuffer->upload(indices.data());
    vertexArray->indexBuffer(std::move(indexBuffer));

    renderer::ClearState clearState{{0, 1, 1, 1}};

    // Add the static matrices as uniforms
    pipeline->uniforms()["bltin_view"] = sceneState.camera().viewMatrix();
    pipeline->uniforms()["bltin_projection"] = sceneState.projectionMatrix();

    // Basic model matrix around the origin
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));

    // Render function
    auto renderFn = [&](renderer::Context &context) {
        // Clear the scene
        clearState.color = {1., 0, 1., 1};
        context.clear(clearState);

        // Update the model uniform
        pipeline->uniforms()["bltin_model"] = model;

        // Draw the rectangle
        context.draw({{}, *pipeline, *vertexArray}, sceneState);
    };

    // Update function
    auto updateFn = [&]() { model = glm::rotate(model, float(M_2_PI) / 10.f, glm::vec3(1.0f, 0.3f, 0.5f)); };

    // Runloop
    window.run(renderFn, updateFn, 60);

    glfwTerminate();
}
