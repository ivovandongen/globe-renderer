#include <glbr/io/http_data_source_curl.hpp>

#include <glbr/core/concurrent/scheduler.hpp>
#include <glbr/core/concurrent/simple_run_loop.hpp>

#include <test.hpp>

#include <chrono>
#include <future>
#include <memory>
#include <thread>

using namespace glbr::io;
using namespace glbr::core::concurrent;
using namespace std::chrono_literals;

class DummyScheduler : public Scheduler {
public:
    DummyScheduler() { Scheduler::Set(this); }
    ~DummyScheduler() override { Scheduler::Set(nullptr); }
    void schedule(WorkTask&& task) override { task(); }
};

TEST(HttpDataSource, Create) {
    auto dataSource = HttpDataSource::Create();
}

TEST(HttpDataSource, Load) {
    DummyScheduler loop;

    // TODO: start a http server
    auto dataSource = HttpDataSource::Create();

    bool loaded = false;
    std::promise<Response> promise;
    auto req = dataSource->load(Resource{"https://www.google.com"}, [&](Response res) {
        loaded = true;
        promise.set_value(std::move(res));
    });

    auto future = promise.get_future();
    future.wait_for(2s);
    ASSERT_TRUE(loaded);
    ASSERT_FALSE(future.get().data().empty());
}

TEST(HttpDataSource, Shutdown) {
    DummyScheduler loop;

    // TODO: start a http server
    auto dataSource = HttpDataSource::Create();

    bool loaded = false;
    std::promise<Response> promise;
    auto req = dataSource->load(Resource{"https://www.google.com"}, [&](Response res) {
      loaded = true;
      promise.set_value(std::move(res));
    });

    auto future = promise.get_future();
    future.wait_for(2s);
    dataSource.reset();
    ASSERT_TRUE(loaded);
    ASSERT_FALSE(future.get().data().empty());
}

TEST(HttpDataSource, CorrectResponseThread) {
    SimpleRunLoop loop;

    // TODO: start a http server
    auto dataSource = HttpDataSource::Create();

    auto threadId = std::this_thread::get_id();
    bool loaded = false;
    std::promise<Response> promise;
    auto req = dataSource->load(Resource{"https://www.google.com"}, [&](const Response&) {
        loaded = true;
        ASSERT_EQ(threadId, std::this_thread::get_id());
    });

    auto future = promise.get_future();
    int iterations = 0;
    while (!loaded && iterations < 200) {
        loop.tick();
        future.wait_for(100ms);
        iterations++;
    }
    ASSERT_TRUE(loaded);
}

TEST(HttpDataSource, DiscardRequest) {
    DummyScheduler loop;
    auto dataSource = HttpDataSource::Create();
    dataSource->load(Resource{"https://www.google.com"}, [&](const Response&) {});
}