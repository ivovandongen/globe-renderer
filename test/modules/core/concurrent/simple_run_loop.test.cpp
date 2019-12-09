#include <glbr/core/concurrent/simple_run_loop.hpp>

#include <test.hpp>

#include <future>
#include <thread>

using namespace glbr::core::concurrent;
using namespace std::chrono_literals;

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
    loop->shutdown();
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
    loop->shutdown();
    thread.join();
}

TEST(SimpleRunLoop, Run) {
    auto loop = std::make_unique<SimpleRunLoop>();
    loop->post([&]() { loop->shutdown(); });
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

auto msSinceEpoch(std::chrono::steady_clock::time_point tp) {
    using namespace std::chrono;
    return duration_cast<milliseconds>(tp.time_since_epoch());
}

TEST(SimpleRunLoop, PostDelayed) {
    using namespace std::chrono;

    auto loop = std::make_unique<SimpleRunLoop>();
    std::promise<steady_clock::time_point> promise;
    auto startTime = steady_clock::now();
    loop->postDelayed(
        [&]() {
            promise.set_value(steady_clock::now());
            loop->shutdown();
        },
        500ms);
    loop->run();

    ASSERT_NEAR(duration_cast<milliseconds>(promise.get_future().get() - startTime).count(), 500, 50);
}

TEST(SimpleRunLoop, PostDelayedSorted) {
    using namespace std::chrono;

    auto loop = std::make_unique<SimpleRunLoop>();
    auto startTime = steady_clock::now();

    std::promise<steady_clock::time_point> promise1;
    loop->postDelayed(
        [&]() {
            promise1.set_value(steady_clock::now());
            loop->shutdown();
        },
        500ms);

    std::promise<steady_clock::time_point> promise2;
    loop->postDelayed([&]() { promise2.set_value(steady_clock::now()); }, 400ms);

    loop->run();

    ASSERT_NEAR(duration_cast<milliseconds>(promise1.get_future().get() - startTime).count(), 500, 50);
    ASSERT_NEAR(duration_cast<milliseconds>(promise2.get_future().get() - startTime).count(), 400, 50);
}

TEST(SimpleRunLoop, PostDelayedSuccessively) {
    using namespace std::chrono;

    auto loop = std::make_unique<SimpleRunLoop>();

    auto startTime = steady_clock::now();
    bool ran = false;

    loop->postDelayed(
        [&]() {
            ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 500, 50);
            ran = true;
        },
        500ms);

    while (!ran) {
        loop->tick();
    }

    startTime = steady_clock::now();
    ran = false;
    loop->postDelayed(
        [&]() {
            ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 500, 50);
            ran = true;
        },
        500ms);

    while (!ran) {
        loop->tick();
    }
}

TEST(SimpleRunLoop, TickDelayedAndRegularCombined) {
    using namespace std::chrono;

    auto loop = std::make_unique<SimpleRunLoop>();

    auto startTime = steady_clock::now();
    std::atomic_int taskCounter{4};

    loop->postDelayed(
        [&]() {
            ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 500, 50);
            taskCounter--;
        },
        500ms);
    loop->post([&]() { taskCounter--; });
    loop->postDelayed(
        [&]() {
            ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 100, 50);
            taskCounter--;
        },
        100ms);
    loop->post([&]() { taskCounter--; });

    while (taskCounter > 0) {
        loop->tick();
    }

    ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 500, 50);
}

TEST(SimpleRunLoop, RunDelayedAndRegularCombined) {
    using namespace std::chrono;

    SimpleRunLoop loop;

    auto startTime = steady_clock::now();
    std::atomic_int taskCounter{4};

    loop.postDelayed(
        [&]() {
            ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 500, 50);
            taskCounter--;
            loop.shutdown();
        },
        500ms);
    loop.post([&]() { taskCounter--; });
    loop.postDelayed(
        [&]() {
            ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 100, 50);
            taskCounter--;
        },
        100ms);
    loop.post([&]() { taskCounter--; });

    loop.run();

    ASSERT_NEAR(duration_cast<milliseconds>(steady_clock::now() - startTime).count(), 500, 50);
}