#pragma once

#include <glbr/core/events/event_handler.hpp>
#include <glbr/core/events/event_producer.hpp>

#include <memory>

namespace glbr {
namespace imgui {

class ImGuiBackend : public core::EventHandler {
public:
    static std::shared_ptr<ImGuiBackend> Instance(core::EventProducer&);

    void operator()(core::Event& event) override;

    ~ImGuiBackend() override;

private:
    explicit ImGuiBackend(core::EventProducer& eventProducer);

private:
    std::unique_ptr<core::EventHandlerRegistration> handlerRegistration_;
};

}  // namespace imgui
}  // namespace glbr