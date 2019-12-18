#pragma once

#include "run_loop.hpp"
#include "simple_run_loop.hpp"

#include <future>
#include <memory>
#include <thread>

namespace glbr {
namespace core {
namespace concurrent {

class ThreadedRunLoop : public RunLoop {
public:
    ThreadedRunLoop() {
        std::promise<void> started;
        thread_ = std::thread([&]() {
            loop_ = std::make_unique<SimpleRunLoop>();
            loop_->schedule([&]() { started.set_value(); });
            loop_->run();
        });
        started.get_future().get();
        assert(loop_);
    }

    ~ThreadedRunLoop() override {
        if (loop_) {
            loop_->shutdown(true);
            loop_.reset();
        }
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    void post(WorkTask&& task) override { loop_->schedule(std::move(task)); }

    void postDelayed(WorkTask&& task, std::chrono::milliseconds delay) override {
        loop_->postDelayed(std::move(task), delay);
    }

    void shutdown() {
        loop_.reset();
        thread_.join();
    }

private:
    std::thread thread_;
    std::unique_ptr<SimpleRunLoop> loop_;
};

}  // namespace concurrent
}  // namespace core
}  // namespace glbr