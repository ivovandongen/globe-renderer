#include <glbr/core/concurrent/scheduler.hpp>

namespace glbr {
namespace core {
namespace concurrent {

Scheduler* Scheduler::Get() {
    return Current();
}

void Scheduler::Set(Scheduler* scheduler) {
    Current() = scheduler;
}

}  // namespace concurrent
}  // namespace core
}  // namespace glbr