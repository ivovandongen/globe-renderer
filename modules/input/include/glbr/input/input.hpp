#pragma once

#include <glbr/input/key_codes.hpp>
#include <glbr/input/key_state.hpp>
#include <glbr/input/mouse_button_codes.hpp>

namespace glbr {
namespace input {

struct Position {
    double x;
    double y;

    static Position INVALID;
};

class Input {
public:
    virtual ~Input() = default;

    virtual KeyState keyState(KeyCode) const = 0;

    virtual KeyState mouseButtonState(MouseButtonCode) const = 0;

    virtual Position mousePosition() const = 0;
};


// Operators
inline bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
inline bool operator!=(const Position& lhs, const Position& rhs) {
    return !(lhs == rhs);
}
inline Position operator-(const Position& lhs, const Position& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}
inline Position operator+(const Position& lhs, const Position& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

}  // namespace input
}  // namespace glbr