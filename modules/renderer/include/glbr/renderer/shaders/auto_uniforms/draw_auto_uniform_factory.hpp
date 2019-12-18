#pragma once

#include <glbr/renderer/context.hpp>
#include <glbr/renderer/draw_state.hpp>
#include <glbr/renderer/scene/scene_state.hpp>

#include "draw_auto_uniform.hpp"

#include <memory>

namespace glbr {
namespace renderer {

class DrawAutoUniformFactory {
public:
    virtual ~DrawAutoUniformFactory() = default;

    virtual DrawAutoUniform operator()(Uniform&) = 0;
};

}  // namespace renderer
}  // namespace glbr