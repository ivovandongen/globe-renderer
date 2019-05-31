#pragma once

#include <ctti/type_id.hpp>

namespace glbr {
namespace core {

class Event {
public:
    using TypeId = uint64_t;

    TypeId type() { return _type; }

    bool handled() { return _handled; }

protected:
    explicit Event(TypeId type) : _type(type) {}

private:
    TypeId _type;
    bool _handled{false};
    friend class EventDispatcher;
};

template <class E>
class EventImpl : public Event {
public:
    static const constexpr TypeId Type() { return ctti::type_id<E>().hash(); }

protected:
    EventImpl() : Event(Type()){};
};

class EventDispatcher {
public:
    explicit EventDispatcher(Event& event) : _event(event) {}

    template <typename T, typename Fn>
    bool dispatch(Fn&& fn) {
        if (_event.type() == T::Type()) {
            _event._handled = fn(static_cast<T&>(_event));
            return true;
        }
        return false;
    }

private:
    Event& _event;
};

}  // namespace core
}  // namespace glbr