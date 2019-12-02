#include <glbr/core/concurrent/scheduler.hpp>

namespace glbr {
namespace core {
namespace concurrent {

Scheduler* Scheduler::Get() {
    return current();
}

void Scheduler::Set(Scheduler* scheduler) {
    current() = scheduler;
}

}  // namespace concurrent
}  // namespace core
}  // namespace glbr