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

}  // namespace geometry
}  // namespace core

namespace scene {
namespace renderables {

class AxisRenderable : public Renderable {
public:
    ~AxisRenderable() = default;

    explicit AxisRenderable(float scale, glm::vec3 position = {0, 0, 0});

    void init(renderer::Context& context) override;

    void render(renderer::Context& context, renderer::SceneState& sceneState) override;

private:
    glm::mat4 model_;
    std::unique_ptr<core::geometry::Mesh> mesh_;

    std::shared_ptr<renderer::Pipeline> pipeline_;
    std::shared_ptr<renderer::VertexArray> vao_;
};

}  // namespace renderables
}  // namespace scene
}  // namespace glbr