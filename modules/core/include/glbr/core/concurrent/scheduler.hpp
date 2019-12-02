#pragma once

#include <functional>
#include <memory>
#include <thread>
#include <utility>

namespace glbr {
namespace core {
namespace concurrent {

class Scheduler {
public:
    using WorkTask = std::function<void()>;

    static Scheduler* Get();

    virtual ~Scheduler() = default;

    virtual void schedule(WorkTask&&) = 0;

protected:
    static void Set(Scheduler* scheduler);

    static Scheduler*& current() {
        static thread_local Scheduler* scheduler;
        return scheduler;
    };
};

}  // namespace concurrent
}  // namespace core
}  // namespace glbr