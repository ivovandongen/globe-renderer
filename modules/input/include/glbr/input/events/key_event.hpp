#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/input/key_codes.hpp>
#include <glbr/input/key_state.hpp>

namespace glbr {
namespace input {

class KeyEvent : public core::EventImpl<KeyEvent> {
public:
    KeyEvent(KeyCode keyCode, KeyState state) : keyCode_(keyCode), state_(state) {}

    KeyCode keyCode() const { return keyCode_; }
    KeyState state() const { return state_; }

    std::string str() const override;

private:
    KeyCode keyCode_;
    KeyState state_;
};

}  // namespace input
}  // namespace glbr