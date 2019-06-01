#pragma once

#include <glbr/input/events/key_event.hpp>

namespace glbr {
namespace renderer {
namespace glfw {

input::KeyEvent convertKeyCode(int key, int action /*TODO: modifiers and scan codes*/);

}  // namespace glfw
}  // namespace renderer
} // namespace glbr