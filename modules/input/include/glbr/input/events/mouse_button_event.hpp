#pragma once

#include <glbr/core/event.hpp>
#include <glbr/input/mouse_button_codes.hpp>

#include <sstream>

namespace glbr {
namespace input {

class MouseButtonEvent : public core::EventImpl<MouseButtonEvent> {
public:
    enum class Action : int { PRESS, RELEASE };

    MouseButtonEvent(MouseButtonCode buttonCode, Action action) : _buttonCode(buttonCode), _action(action) {}

    MouseButtonCode buttonCode() const { return _buttonCode; }
    Action action() const { return _action; }

    std::string str() override;

private:
    MouseButtonCode _buttonCode;
    Action _action;
};

std::ostream& operator<<(std::ostream& os, const MouseButtonEvent::Action& action);

}  // namespace input
}  // namespace glbr