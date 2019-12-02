#include <glbr/core/concurrent/threaded_run_loop.hpp>

#include <test.hpp>

#include <future>
#include <thread>

using namespace glbr::core::concurrent;

TEST(ThreadedRunLoop, LifeCycle) {
    ThreadedRunLoop loop;

    std::promise<bool> status;
    loop.post([&]() { status.set_value(true); });
    ASSERT_TRUE(status.get_future().get());
}

TEST(ThreadedRunLoop, Shutdown) {
    ThreadedRunLoop loop;
    loop.post([&]() {});
    loop.shutdown();
}