#include <glbr/input/events/mouse_button_event.hpp>

#include <sstream>

namespace glbr {
namespace input {

std::string MouseButtonEvent::str() {
    std::stringstream ss;
    ss << EventImpl::str() << "[" << _buttonCode << ": " << _state << "]";
    return ss.str();
}

}  // namespace input
}  // namespace glbr