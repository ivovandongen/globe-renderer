#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/input/key_state.hpp>
#include <glbr/input/mouse_button_codes.hpp>

namespace glbr {
namespace input {

class MouseButtonEvent : public core::EventImpl<MouseButtonEvent> {
public:
    MouseButtonEvent(MouseButtonCode buttonCode, KeyState state) : _buttonCode(buttonCode), _state(state) {}

    MouseButtonCode buttonCode() const { return _buttonCode; }
    KeyState state() const { return _state; }

    std::string str() const override;

private:
    MouseButtonCode _buttonCode;
    KeyState _state;
};

}  // namespace input
}  // namespace glbr