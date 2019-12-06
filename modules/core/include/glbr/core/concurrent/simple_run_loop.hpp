#pragma once

#include "run_loop.hpp"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace glbr {
namespace core {
namespace concurrent {

class SimpleRunLoop : public RunLoop {
public:
    SimpleRunLoop();
    ~SimpleRunLoop() override;

    void post(WorkTask&& task) override;

    void run();

    void tick(bool emptyQueue = false);

private:
    std::condition_variable cv_;
    std::mutex mutex_;
    std::atomic_bool running_{true};
    std::queue<Scheduler::WorkTask> tasks_;
};

}  // namespace concurrent
}  // namespace core
}  // namespace glbr