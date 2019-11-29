#include <glbr/core/concurrent/thread_pool.hpp>

#include <test.hpp>

#include <future>

using namespace glbr::core::concurrent;

TEST(ThreadPool, SetupTearDown) {
    ThreadPool pool;
}

TEST(ThreadPool, DoWorkSequentially) {
    ThreadPool pool{1};

    int result = 2;
    std::promise<bool> promise;
    pool.submit([&] { result *= 2; });
    pool.submit([&] { promise.set_value(true); });

    ASSERT_TRUE(promise.get_future().get());
    ASSERT_EQ(4, result);
}
