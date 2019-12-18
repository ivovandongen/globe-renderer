#include <glbr/input/events/key_event.hpp>

#include <sstream>

namespace glbr {
namespace input {

std::string KeyEvent::str() const {
    std::stringstream ss;
    ss << EventImpl::str() << "[" << keyCode_ << ": " << state_ << "]";
    return ss.str();
}

}  // namespace input
}  // namespace glbr