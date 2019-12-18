#include <glbr/input/events/char_event.hpp>

#include <sstream>

namespace glbr {
namespace input {

std::string CharEvent::str() const {
    std::stringstream ss;
    ss << EventImpl::str() << "[" << character_ << "]";
    return ss.str();
}

}  // namespace input
}  // namespace glbr