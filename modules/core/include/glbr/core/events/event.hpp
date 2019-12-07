#pragma once

#include <ctti/type_id.hpp>

#include <string>

namespace glbr {
namespace core {

/**
 * Event base class.
 */
class Event {
public:
    using TypeId = uint64_t;

    virtual ~Event() = default;

    TypeId type() const { return _type; }

    bool handled() const { return _handled; }

    virtual std::string str() const = 0;

protected:
    explicit Event(TypeId type) : _type(type) {}

private:
    TypeId _type;
    bool _handled{false};
    friend class EventDispatcher;
};

/**
 * Helper template that establishes an constexpr id for the Event subclass.
 *
 * @tparam E The concrete Event subclass
 */
template <class E>
class EventImpl : public Event {
public:
    static constexpr TypeId Type() { return ctti::type_id<E>().hash(); }

    std::string str() const override { return ctti::nameof<E>().str(); }

protected:
    EventImpl() : Event(Type()){};
};

/**
 * Event dispatcher. Can be used instead of switch statement if convenient.
 *
 */
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