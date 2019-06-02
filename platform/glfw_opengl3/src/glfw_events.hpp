#pragma once

#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_button_event.hpp>

namespace glbr {
namespace renderer {
namespace glfw {

input::KeyState convertKeyState(int action);

int convertKeyCode(input::KeyCode);

int convertMouseButtonCode(input::MouseButtonCode code);

input::MouseButtonCode convertMouseButton(int code);

input::KeyEvent convertKeyEvent(int key, int action /*TODO: modifiers and scan codes*/);

input::MouseButtonEvent convertMouseButtonEvent(int key, int action /*TODO: modifiers and scan codes*/);

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr