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
        thread = std::thread([&]() {
            loop_ = std::make_unique<SimpleRunLoop>();
            loop_->schedule([&]() { started.set_value(); });
            loop_->run();
        });
        started.get_future().get();
        assert(loop_);
    }

    ~ThreadedRunLoop() override {
        if (loop_) {
            loop_.reset();
        }
        if (thread.joinable()) {
            thread.join();
        }
    }

    void post(WorkTask&& task) override { loop_->schedule(std::move(task)); }

    void shutdown() {
        loop_.reset();
        thread.join();
    }

private:
    std::thread thread;
    std::unique_ptr<SimpleRunLoop> loop_;
};

}  // namespace concurrent
}  // namespace core
}