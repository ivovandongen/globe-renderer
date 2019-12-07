#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/input/key_codes.hpp>
#include <glbr/input/key_state.hpp>

namespace glbr {
namespace input {

class KeyEvent : public core::EventImpl<KeyEvent> {
public:
    KeyEvent(KeyCode keyCode, KeyState state) : _keyCode(keyCode), _state(state) {}

    KeyCode keyCode() const { return _keyCode; }
    KeyState state() const { return _state; }

    std::string str() const override;

private:
    KeyCode _keyCode;
    KeyState _state;
};

}  // namespace input
}  // namespace glbr