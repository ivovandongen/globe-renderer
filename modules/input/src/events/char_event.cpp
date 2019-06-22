#include <glbr/input/events/char_event.hpp>

#include <sstream>

namespace glbr {
namespace input {

std::string CharEvent::str() {
    std::stringstream ss;
    ss << EventImpl::str() << "[" << _character << "]";
    return ss.str();
}

}  // namespace input
}  // namespace glbr