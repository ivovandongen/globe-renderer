#pragma once

#include <ostream>

namespace glbr {
namespace input {

enum class KeyState : int { PRESS, RELEASE, REPEAT };

std::ostream& operator<<(std::ostream& os, const KeyState& action);

}  // namespace input
}  // namespace glbr