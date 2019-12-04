#include <glbr/core/concurrent/simple_run_loop.hpp>

namespace glbr {
namespace core {
namespace concurrent {

SimpleRunLoop::SimpleRunLoop() {
    Scheduler::Set(this);
};

SimpleRunLoop::~SimpleRunLoop() {
    running_ = false;
    cv_.notify_one();
};

void SimpleRunLoop::post(RunLoop::WorkTask&& task) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        tasks_.push(std::move(task));
    }
    cv_.notify_one();
}

void SimpleRunLoop::run() {
    while (running_) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !running_ || !tasks_.empty(); });
        if (running_ && !tasks_.empty()) {
            auto task = std::move(tasks_.front());
            tasks_.pop();
            lock.unlock();
            task();
        }
    }
}

void SimpleRunLoop::tick() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (!tasks_.empty()) {
        auto task = std::move(tasks_.front());
        tasks_.pop();
        lock.unlock();
        task();
    }
}

}  // namespace concurrent
}  // namespace core
}  // namespace glbr