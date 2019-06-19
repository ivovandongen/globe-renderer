#pragma once

#include <glbr/core/events/event_handler.hpp>

#include <memory>

namespace glbr {
namespace imgui {

class ImGuiBackend : public core::EventHandler {
public:
    static std::shared_ptr<ImGuiBackend> instance();

    void operator()(core::Event& event) override;

    ~ImGuiBackend() override;

private:
    ImGuiBackend();
};

}  // namespace imgui
}  // namespace glbr