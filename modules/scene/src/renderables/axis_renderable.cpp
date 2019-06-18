#include <glbr/scene/renderables/axis_renderable.hpp>

#include <glbr/core/maths.hpp>

#include <glm/gtc/matrix_transform.hpp>

const constexpr static char* VERTEX_SRC = R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 v_color;

uniform mat4 bltin_model;
uniform mat4 bltin_view;
uniform mat4 bltin_projection;

void main() {
    gl_Position = bltin_projection * bltin_view * bltin_model * vec4(position, 1.0);
    v_color = color;
}
)";

const constexpr static char* FRAGMENT_SRC = R"(
#version 330 core

out vec4 fragColor;

in vec3 v_color;

void main() {
    fragColor = vec4(v_color, 1.0);
}
)";

namespace glbr {
namespace scene {
namespace renderables {

using namespace glbr::core;
using namespace glbr::core::geometry;
using namespace glbr::renderer;

static std::unique_ptr<Mesh> createMesh() {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };
    using Index = std::array<int, 2>;

    auto mesh = Mesh::Create<Vertex, Index>(
        {
            {"position", VertexAttributeType::Float, 3},                       // Vertex position
            {"color", VertexAttributeType::Float, 3, offsetof(Vertex, color)}  // Vertex color
        },
        PrimitiveType::LINES);

    mesh->data({
        {{-1.0f, 0.0f, 0.0f}, {1.f, 0.f, 0.f}},  // min x
        {{1.0f, 0.0f, 0.0f}, {1.f, 0.f, 0.f}},   // max x

        {{0.0f, -1.0f, 0.0f}, {0.f, 1.f, 0.f}},  // min y
        {{0.0f, 1.0f, 0.0f}, {0.f, 1.f, 0.f}},   // max y

        {{0.0f, 0.0f, -1.0f}, {0.f, 0.f, 1.f}},  // min z
        {{0.0f, 0.0f, 1.0f}, {0.f, 0.f, 1.f}}    // max z
    });

    mesh->indices({
        {0, 1},  // x axis
        {2, 3},  // y axis
        {4, 5},  // z axis
    });

    return mesh;
}
AxisRenderable::AxisRenderable(float scale, glm::vec3 position) : _model(glm::mat4(1.0f)) {
    // Create model matrix
    _model = glm::translate(_model, position);
    _model = glm::scale(_model, glm::vec3(scale, scale, scale));

    // Create mesh
    _mesh = createMesh();
}

void AxisRenderable::init(const renderer::Device& device, const renderer::Context& context) {
    // Create the pipeline
    _pipeline = device.createPipeline(VERTEX_SRC, FRAGMENT_SRC);

    // Create the VAO
    _vao = context.createVertexArray(*_mesh);
}

void AxisRenderable::render(renderer::Context& context, renderer::SceneState& sceneState) {
    // Set the model matrix
    sceneState.modelMatrix(_model);

    // Draw
    context.draw(_mesh->primitiveType(), {{}, _pipeline, _vao}, sceneState);
}

}  // namespace renderables
}  // namespace scene
}  // namespace glbr