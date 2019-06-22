#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/input/key_codes.hpp>
#include <glbr/input/key_state.hpp>

namespace glbr {
namespace input {

class CharEvent : public core::EventImpl<CharEvent> {
public:
    using Char = unsigned int;
    explicit CharEvent(Char character) : _character(character) {}

    Char character() const { return _character; }

    std::string str() override;

private:
    Char _character;
};

}  // namespace input
}  // namespace glbr