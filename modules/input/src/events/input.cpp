#include <glbr/input/input.hpp>

#include <limits>

namespace glbr {
namespace input {

Position Position::INVALID = Position{std::numeric_limits<double>::min(), std::numeric_limits<double>::min()};

}  // namespace input
}  // namespace glbr