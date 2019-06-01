#include <glbr/input/events/key_event.hpp>

namespace glbr {
namespace input {

std::string KeyEvent::str() {
    std::stringstream ss;
    ss << EventImpl::str() << "[" << _keyCode << ": " << _action << "]";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const KeyEvent::Action& action) {
    switch (action) {
        case KeyEvent::Action::PRESS:
            os << "PRESS";
            break;
        case KeyEvent::Action::RELEASE:
            os << "RELEASE";
            break;
        case KeyEvent::Action::REPEAT:
            os << "REPEAT";
            break;
    }
    return os;
}

}  // namespace input
}  // namespace glbr