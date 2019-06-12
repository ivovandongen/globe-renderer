#pragma once

#include "event.hpp"

namespace glbr {
namespace core {

using EventHandlingFN = std::function<void(Event&)>;

class EventHandler {
public:
    virtual ~EventHandler() = default;

    virtual void operator()(Event& event) = 0;
};

}  // namespace core
}  // namespace glbr