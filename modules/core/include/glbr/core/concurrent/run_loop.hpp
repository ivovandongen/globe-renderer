#pragma once

#include "scheduler.hpp"

#include <functional>

namespace glbr {
namespace core {
namespace concurrent {

class RunLoop : public Scheduler {
public:
    using WorkTask = std::function<void()>;

    ~RunLoop() override = default;

    virtual void post(WorkTask&&) = 0;

    void schedule(Scheduler::WorkTask&& wt) override { post(std::move(wt)); }
};

}  // namespace concurrent
}  // namespace core
}  // namespace glbr