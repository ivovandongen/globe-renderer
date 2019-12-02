#pragma once

#include "scheduler.hpp"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace glbr {
namespace core {
namespace concurrent {

class ThreadPool : Scheduler {
public:
    explicit ThreadPool(int poolSize = 1, const char* name = "Threadpool");

    ~ThreadPool() override;

    void schedule(Scheduler::WorkTask&&) override;

private:
    std::string name_;
    std::condition_variable cv_;
    std::mutex mutex_;
    std::atomic_bool running_{true};
    std::vector<std::thread> workers_;
    std::queue<Scheduler::WorkTask> tasks_;
};

}  // namespace concurrent
}  // namespace core
}  // namespace glbr