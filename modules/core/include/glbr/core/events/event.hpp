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

    inline TypeId type() const { return type_; }

    inline bool handled() const { return handled_; }

    virtual std::string str() const = 0;

protected:
    explicit Event(TypeId type) : type_(type) {}

private:
    TypeId type_;
    bool handled_{false};
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
    EventImpl();
};

template <class E>
EventImpl<E>::EventImpl() : Event(Type()) {}

/**
 * Event dispatcher. Can be used instead of switch statement if convenient.
 *
 */
class EventDispatcher {
public:
    explicit EventDispatcher(Event& event) : event_(event) {}

    template <typename T, typename Fn>
    bool dispatch(Fn&& fn) {
        if (event_.type() == T::Type()) {
            event_.handled_ = fn(static_cast<T&>(event_));
            return true;
        }
        return false;
    }

private:
    Event& event_;
};

}  // namespace core
}  // namespace glbr