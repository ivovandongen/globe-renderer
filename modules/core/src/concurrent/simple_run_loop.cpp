#include <glbr/core/concurrent/simple_run_loop.hpp>

#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

namespace glbr {
namespace core {
namespace concurrent {

SimpleRunLoop::SimpleRunLoop() {
    Scheduler::Set(this);
};

SimpleRunLoop::~SimpleRunLoop() {
    shutdown(true);
};

void SimpleRunLoop::shutdown(bool block) {
    if (running_) {
        running_ = false;
        cv_.notify_one();

        if (block && !shutdown_) {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this]() { return bool(shutdown_); });
        }
    }
}

void SimpleRunLoop::post(RunLoop::WorkTask&& task) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        tasks_.push(std::move(task));
    }
    cv_.notify_one();
}

void SimpleRunLoop::postDelayed(RunLoop::WorkTask&& task, milliseconds delay) {
    // Shortcut if delay is 0
    if (delay == 0ms) {
        post(std::forward<RunLoop::WorkTask>(task));
        return;
    }

    auto now = steady_clock::now();
    auto alarmTime = now + delay;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        scheduledTasks_.insert({alarmTime, std::move(task)});

        if (nextAlarm_ > alarmTime) {
            nextAlarm_ = alarmTime;
        }
    }

    cv_.notify_one();
}

void SimpleRunLoop::run() {
    running_ = true;
    while (running_) {
        std::unique_lock<std::mutex> lock(mutex_);
        auto pred = [this] {
            return !running_ || !tasks_.empty() || (!scheduledTasks_.empty() && nextAlarm_ <= steady_clock::now());
        };
        if (scheduledTasks_.empty()) {
            cv_.wait(lock, pred);
        } else {
            cv_.wait_until(lock, nextAlarm_, pred);
        }

        if (!running_) {
            break;
        }

        // Process all scheduled tasks
        processScheduledTasks(lock);

        // Handle the main queue
        if (!tasks_.empty()) {
            auto task = std::move(tasks_.front());
            tasks_.pop();
            lock.unlock();
            task();
        }
    }

    // Signal that shutdown is complete in case someone is waiting for it
    shutdown_ = true;
    cv_.notify_one();
}

void SimpleRunLoop::tick(bool emptyQueue) {
    std::unique_lock<std::mutex> lock(mutex_);

    // Handle the scheduled tasks always
    processScheduledTasks(lock);

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

void SimpleRunLoop::processScheduledTasks(std::unique_lock<std::mutex>& lock) {
    assert(lock.owns_lock());

    if (!scheduledTasks_.empty()) {
        for (auto it = std::begin(scheduledTasks_);
             it != std::end(scheduledTasks_) && it->timePoint <= steady_clock::now();
             scheduledTasks_.erase(it++)) {
            lock.unlock();
            it->task();
            lock.lock();
        }

        // Make sure to update the next alarm time
        nextAlarm_ = scheduledTasks_.empty() ? steady_clock::time_point::max() : std::begin(scheduledTasks_)->timePoint;
    }
}

}  // namespace concurrent
}  // namespace core
}  // namespace glbr