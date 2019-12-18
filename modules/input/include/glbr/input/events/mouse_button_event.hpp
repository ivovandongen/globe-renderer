#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/input/key_state.hpp>
#include <glbr/input/mouse_button_codes.hpp>

namespace glbr {
namespace input {

class MouseButtonEvent : public core::EventImpl<MouseButtonEvent> {
public:
    MouseButtonEvent(MouseButtonCode buttonCode, KeyState state) : buttonCode_(buttonCode), state_(state) {}

    MouseButtonCode buttonCode() const { return buttonCode_; }
    KeyState state() const { return state_; }

    std::string str() const override;

private:
    MouseButtonCode buttonCode_;
    KeyState state_;
};

}  // namespace input
}  // namespace glbr