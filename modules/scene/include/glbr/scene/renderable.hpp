#pragma once

#include <glbr/renderer/context.hpp>
#include <glbr/renderer/device.hpp>
#include <glbr/renderer/scene/scene_state.hpp>

namespace glbr {
namespace scene {

class Renderable {
public:
    ~Renderable() = default;

    virtual void init(renderer::Context& context){};

    virtual void update(std::chrono::nanoseconds interval, const renderer::SceneState& sceneState){};

    virtual void render(renderer::Context& context, renderer::SceneState& sceneState) = 0;
};

}  // namespace scene
}  // namespace glbr