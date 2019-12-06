#include <glbr/core/concurrent/simple_run_loop.hpp>

#include <algorithm>

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

void SimpleRunLoop::tick(bool emptyQueue) {
    std::unique_lock<std::mutex> lock(mutex_);

    // Either run 0, once or the number of tasks in the queue currently
    size_t taskCount = emptyQueue ? tasks_.size() : std::min<size_t>(tasks_.size(), 1);

    for (size_t i = 0; i < taskCount; i++) {
        auto task = std::move(tasks_.front());
        tasks_.pop();
        lock.unlock();
        task();

        if (i + 1 < taskCount) {
            lock.lock();
        }
    }
}

}  // namespace concurrent
}  // namespace core
}  // namespace glbr