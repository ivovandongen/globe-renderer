#include <glbr/renderer/window_resized_event.hpp>

#include <sstream>

namespace glbr {
namespace renderer {

std::string WindowResizedEvent::str() const {
    std::stringstream ss;
    ss << EventImpl::str() << "[" << size_.width << "," << size_.height << "]";
    return ss.str();
}

}  // namespace renderer
}  // namespace glbr
