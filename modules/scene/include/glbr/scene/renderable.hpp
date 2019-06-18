#pragma once

#include <glbr/renderer/context.hpp>
#include <glbr/renderer/device.hpp>
#include <glbr/renderer/scene/scene_state.hpp>

namespace glbr {
namespace scene {

class Renderable {
public:
    ~Renderable() = default;

    virtual void init(const renderer::Device& device, const renderer::Context& context){};

    virtual void render(renderer::Context& context, renderer::SceneState& sceneState) = 0;
};

}  // namespace scene
}  // namespace glbr