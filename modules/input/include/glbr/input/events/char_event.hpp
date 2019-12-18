#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/input/key_codes.hpp>
#include <glbr/input/key_state.hpp>

namespace glbr {
namespace input {

class CharEvent : public core::EventImpl<CharEvent> {
public:
    using Char = unsigned int;
    explicit CharEvent(Char character) : character_(character) {}

    Char character() const { return character_; }

    std::string str() const override;

private:
    Char character_;
};

}  // namespace input
}  // namespace glbr