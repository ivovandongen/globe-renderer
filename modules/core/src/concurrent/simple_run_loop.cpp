#include <glbr/core/concurrent/simple_run_loop.hpp>

namespace glbr {
namespace core {
namespace concurrent {

SimpleRunLoop::SimpleRunLoop() {
    Scheduler::Set(this);
};

SimpleRunLoop::~SimpleRunLoop() {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    running_ = false;
};

void SimpleRunLoop::post(RunLoop::WorkTask&& task) {
    {
        std::unique_lock<std::recursive_mutex> lock(mutex_);
        tasks_.push(std::move(task));
    }
    cv_.notify_one();
}

void SimpleRunLoop::run() {
    while (running_) {
        tick();
    }
}

void SimpleRunLoop::tick() {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
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