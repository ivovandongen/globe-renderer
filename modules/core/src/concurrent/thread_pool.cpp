#include <glbr/core/concurrent/thread_pool.hpp>

#include <glbr/logging/logging.hpp>

namespace glbr {
namespace core {
namespace concurrent {

ThreadPool::ThreadPool(int poolSize, const char* name) : name_(name) {
    assert(poolSize > 0);
    logging::info("Starting scheduler {}");

    for (int i = 0; i < poolSize; i++) {
        workers_.emplace_back([&, worker_id = i]() {
            logging::info("{} - Starting worker thread {}", name_, worker_id);
            while (true) {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this] { return !tasks_.empty() || !running_; });

                if (!running_) {
                    break;
                }

                if (!tasks_.empty()) {
                    auto task = std::move(tasks_.front());
                    tasks_.pop();
                    lock.unlock();
                    task();
                }
            }

            logging::info("{} - Exiting worker thread {}", name_, worker_id);
        });
    }
}

ThreadPool::~ThreadPool() {
    logging::info("Halting scheduler {}", name_);
    running_ = false;
    cv_.notify_all();
    for (auto& worker : workers_) {
        worker.join();
    }
}

void ThreadPool::schedule(Scheduler::WorkTask&& task) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        tasks_.push(std::move(task));
    }
    cv_.notify_one();
}

}  // namespace concurrent
}  // namespace core
}  // namespace glbr