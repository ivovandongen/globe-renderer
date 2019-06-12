#pragma once

#include "event_handler.hpp"

#include <functional>

namespace glbr {
namespace core {

class EventProducer {
public:
    virtual ~EventProducer() = default;

    /**
     * Can take either a EventHandlingFN or a EventHandler subclass.
     */
    virtual void registerHandler(const EventHandlingFN&) = 0;
};

}  // namespace core
}  // namespace glbr