#include <glbr/core/geometry/mesh.hpp>
#include <glbr/io/file.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <memory>

using namespace glbr;
using namespace glbr::core::geometry;
using namespace glbr::renderer;

static std::unique_ptr<Mesh> createMesh() {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };
    using Index = std::array<int, 3>;

    auto mesh = Mesh::Create<Vertex, Index>({
        {"position", VertexAttributeType::Float, 3},                       // Vertex position
        {"color", VertexAttributeType::Float, 3, offsetof(Vertex, color)}  // Vertex color
    });

    mesh->data({
        {{0.5f, 0.5f, 0.0f}, {1.f, 0.f, 0.f}},    // top right
        {{0.5f, -0.5f, 0.0f}, {0.f, 1.f, 0.f}},   // bottom right
        {{-0.5f, -0.5f, 0.0f}, {0.f, 0.f, 1.f}},  // bottom left
        {{-0.5f, 0.5f, 0.0f}, {0.f, 0.f, 0.f}}    // top left
    });

    mesh->indices({
        {0, 1, 3},  // first triangle
        {1, 2, 3}   // second triangle
    });

    return mesh;
}

int main() {
    int width = 640, height = 480;

    // Mesh can be created without a current context
    auto mesh = createMesh();

    logging::setLevel(logging::Level::DEBUG);
    logging::info("Starting app");

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

    // Create a vertex array from the mesh
    auto vertexArray = window.context().createVertexArray(*mesh);
    vertexArray->bind();

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
}
