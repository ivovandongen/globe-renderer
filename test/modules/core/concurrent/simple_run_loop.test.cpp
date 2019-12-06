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
    auto loop = std::make_unique<SimpleRunLoop>();
    std::thread thread([&]() {
        started.set_value();
        loop->run();
    });

    started.get_future().get();
    loop->post([&]() {});
    loop.reset();
    thread.join();
}

TEST(SimpleRunLoop, TaskExecutedOnCorrectThread) {
    // Create a loop on a separate thread
    std::promise<void> started;
    auto loop = std::make_unique<SimpleRunLoop>();
    std::__thread_id loopThreadId;
    std::thread thread([&]() {
        loopThreadId = std::this_thread::get_id();
        started.set_value();
        loop->run();
    });
    started.get_future().get();

    std::promise<void> taskExecuted;
    loop->post([&]() {
        ASSERT_EQ(loopThreadId, std::this_thread::get_id());
        taskExecuted.set_value();
    });

    taskExecuted.get_future().get();
    loop.reset();
    thread.join();
}

TEST(SimpleRunLoop, Run) {
    auto loop = std::make_unique<SimpleRunLoop>();
    loop->post([&]() { loop.reset(); });
    loop->run();
}

TEST(SimpleRunLoop, Tick) {
    auto loop = std::make_unique<SimpleRunLoop>();

    bool task1Ran = false;
    loop->post([&]() { task1Ran = true; });

    bool task2Ran = false;
    loop->post([&]() { task2Ran = true; });

    loop->tick();

    ASSERT_TRUE(task1Ran);
    ASSERT_FALSE(task2Ran);
}

TEST(SimpleRunLoop, TickTillEmpty) {
    auto loop = std::make_unique<SimpleRunLoop>();

    bool task1Ran = false;
    loop->post([&]() { task1Ran = true; });

    bool task2Ran = false;
    loop->post([&]() { task2Ran = true; });

    loop->tick(true);

    ASSERT_TRUE(task1Ran);
    ASSERT_TRUE(task2Ran);
}

TEST(SimpleRunLoop, TickTillEmptyAndNoFurther) {
    auto loop = std::make_unique<SimpleRunLoop>();

    bool task1Ran = false;
    loop->post([&]() { task1Ran = true; });

    bool task2Ran = false;
    bool task3Ran = false;
    loop->post([&]() {
        task2Ran = true;
        loop->post([&]() { task3Ran = true; });
    });

    loop->tick(true);

    ASSERT_TRUE(task1Ran);
    ASSERT_TRUE(task2Ran);

    // Tasks added after loop->tick should not be executed to avoid running indefinitely
    ASSERT_FALSE(task3Ran);
}