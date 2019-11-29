#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace glbr {
namespace core {
namespace concurrent {

class ThreadPool {
public:
    explicit ThreadPool(int poolSize = 1, const char* name = "Threadpool");

    ~ThreadPool();

    void submit(std::function<void()>&& task);

private:
    std::string name_;
    std::condition_variable cv_;
    std::mutex mutex_;
    std::atomic_bool terminated_{false};
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
};

}  // namespace concurrent
}  // namespace core
}  // namespace glbr