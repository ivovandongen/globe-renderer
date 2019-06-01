#include <glbr/input/events/mouse_button_event.hpp>

namespace glbr {
namespace input {

std::string MouseButtonEvent::str() {
    std::stringstream ss;
    ss << EventImpl::str() << "[" << _buttonCode << ": " << _action << "]";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const MouseButtonEvent::Action& action) {
    switch (action) {
        case MouseButtonEvent::Action::PRESS:
            os << "PRESS";
            break;
        case MouseButtonEvent::Action::RELEASE:
            os << "RELEASE";
            break;
    }
    return os;
}

}  // namespace input
}  // namespace glbr