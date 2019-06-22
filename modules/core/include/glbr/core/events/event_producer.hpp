#pragma once

#include "event_handler.hpp"

#include <functional>
#include <memory>

namespace glbr {
namespace core {

class EventHandlerRegistration {
public:
    virtual ~EventHandlerRegistration() = default;
};

class EventProducer {
public:
    virtual ~EventProducer() = default;

    /**
     * Can take either an EventHandlingFN.
     */
    virtual std::unique_ptr<EventHandlerRegistration> registerHandler(const EventHandlingFN&) = 0;

    /**
     * Can take either an EventHandler subclass.
     */
    std::unique_ptr<EventHandlerRegistration> registerHandler(EventHandler& handler) {
        return registerHandler([&](Event& event) { handler(event); });
    };
};

}  // namespace core
}  // namespace glbr