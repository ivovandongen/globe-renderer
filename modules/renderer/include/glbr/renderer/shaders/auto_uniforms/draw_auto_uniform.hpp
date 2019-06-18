#pragma once

#include <glbr/renderer/context.hpp>
#include <glbr/renderer/draw_state.hpp>
#include <glbr/renderer/scene/scene_state.hpp>

namespace glbr {
namespace renderer {

using DrawAutoUniform = std::function<void(const Context&, const DrawState&, const SceneState&)>;

}  // namespace renderer
}  // namespace glbr