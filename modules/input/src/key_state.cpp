#include <glbr/input/key_state.hpp>

namespace glbr {
namespace input {

std::ostream& operator<<(std::ostream& os, const KeyState& action) {
    switch (action) {
        case KeyState::PRESS:
            os << "PRESS";
            break;
        case KeyState::RELEASE:
            os << "RELEASE";
            break;
        case KeyState::REPEAT:
            os << "REPEAT";
            break;
    }
    return os;
}

}  // namespace input
} // namespace glbr