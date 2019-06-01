#pragma once

#include <glbr/core/event.hpp>
#include <glbr/input/key_codes.hpp>

#include <sstream>

namespace glbr {
namespace input {

class KeyEvent : public core::EventImpl<KeyEvent> {
public:
    enum class Action : int { PRESS, RELEASE, REPEAT };

    KeyEvent(KeyCode keyCode, Action action) : _keyCode(keyCode), _action(action) {}

    KeyCode keyCode() const { return _keyCode; }
    Action action() const { return _action; }

    std::string str() override;

private:
    KeyCode _keyCode;
    Action _action;
};

std::ostream& operator<<(std::ostream& os, const KeyEvent::Action& action);

}  // namespace input
}  // namespace glbr