#include <test.hpp>

#include <glbr/core/events/event.hpp>

using namespace glbr::core;

class EventA : public EventImpl<EventA> {};

class EventB : public EventImpl<EventB> {};

TEST(Event, Basic) {
    ASSERT_EQ(EventA::Type(), EventA::Type());
    ASSERT_EQ(EventA::Type(), EventA().type());

    ASSERT_EQ(EventB::Type(), EventB::Type());
    ASSERT_EQ(EventB::Type(), EventB().type());

    ASSERT_NE(EventA::Type(), EventB::Type());
}

TEST(Event, Switchable) {
    auto a = std::make_unique<EventA>();
    switch (a->type()) {
        case EventA::Type():
            SUCCEED();
            break;
        case EventB::Type():
        default:
            FAIL();
    }
}

TEST(Event, Dispatcher) {
    auto a = std::make_unique<EventA>();

    EventDispatcher d(*a);

    ASSERT_FALSE(d.dispatch<EventB>([](auto& e) -> bool { return true; }));
    ASSERT_FALSE(a->handled());

    ASSERT_TRUE(d.dispatch<EventA>([](auto& e) { return true; }));
    ASSERT_TRUE(a->handled());
}
