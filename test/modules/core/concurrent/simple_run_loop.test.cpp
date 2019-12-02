#include <glbr/core/concurrent/simple_run_loop.hpp>

#include <test.hpp>

#include <future>
#include <thread>

using namespace glbr::core::concurrent;

TEST(SimpleRunLoop, LifeCycle) {
    SimpleRunLoop loop;

    bool ran = false;
    loop.post([&]() { ran = true; });
    loop.tick();
    ASSERT_TRUE(ran);
}

TEST(SimpleRunLoop, Shutdown) {
    std::promise<void> started;
    auto  loop = std::make_unique<SimpleRunLoop>();
    std::thread thread([&]() {
        started.set_value();
        loop->run();
    });

    started.get_future().get();
    loop->post([&]() {});
    loop.reset();
    thread.join();
}