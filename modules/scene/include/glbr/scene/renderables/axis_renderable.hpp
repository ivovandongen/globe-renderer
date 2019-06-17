#pragma once

#include <glbr/scene/renderable.hpp>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace glbr {

namespace renderer {

class Pipeline;
class VertexArray;

}  // namespace renderer

namespace core {
namespace geometry {

class Mesh;

} // namespace geometry
}  // namespace core

namespace scene {
namespace renderables {

class AxisRenderable : public Renderable {
public:
    ~AxisRenderable() = default;

    explicit AxisRenderable(float scale, glm::vec3 position = {0, 0, 0});

    void init(const renderer::Device& device, const renderer::Context& context) override;

    void render(renderer::Context& context, const renderer::SceneState& sceneState) override;

private:
    glm::mat4 _model;
    std::unique_ptr<core::geometry::Mesh> _mesh;

    std::shared_ptr<renderer::Pipeline> _pipeline;
    std::shared_ptr<renderer::VertexArray> _vao;
};

}  // namespace renderables
}  // namespace scene
} // namespace glbr