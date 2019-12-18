#pragma once

#include "run_loop.hpp"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <set>

namespace glbr {
namespace core {
namespace concurrent {

class SimpleRunLoop : public RunLoop {
public:
    SimpleRunLoop();
    ~SimpleRunLoop() override;

    void post(WorkTask&& task) override;

    void postDelayed(WorkTask&& task, std::chrono::milliseconds delay) override;

    void run();

    void tick(bool emptyQueue = false);

    void shutdown(bool block = false);

private:
    // Needs mutex to be locked beforehand!
    void processScheduledTasks(std::unique_lock<std::mutex>& lock);

private:
    // Basics
    std::condition_variable cv_;
    std::mutex mutex_;
    std::atomic_bool running_{false};
    std::atomic_bool shutdown_{false};

    // Tasks
    std::queue<Scheduler::WorkTask> tasks_;

    // Scheduling
    using TimePoint = std::chrono::steady_clock::time_point;
    struct ScheduledWorkTask {
        TimePoint timePoint;
        WorkTask task;

        bool operator<(const ScheduledWorkTask& rhs) const { return timePoint < rhs.timePoint; }
    };

    std::chrono::steady_clock::time_point nextAlarm{std::chrono::steady_clock::time_point::max()};
    std::set<ScheduledWorkTask> scheduledTasks_;
};

}  // namespace concurrent
}  // namespace core
}  // namespace glbr