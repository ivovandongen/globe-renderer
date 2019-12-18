#pragma once

#include <glbr/core/events/event_producer.hpp>
#include <glbr/scene/renderable.hpp>

#include <memory>
#include <vector>

class ImDrawData;

namespace glbr {
namespace imgui {

class ImGuiBackend;

using ImGuiRenderable = std::function<void()>;

class ImGuiLayer : public scene::Renderable {
public:
    explicit ImGuiLayer(core::EventProducer&);

    void addRenderable(const ImGuiRenderable& renderable) { renderables_.push_back(renderable); }

    void init(renderer::Context& context) override;

    void render(renderer::Context& context, renderer::SceneState& sceneState) override;

private:
    void renderDrawData(renderer::Context& context, const renderer::SceneState& sceneState, ImDrawData* drawData);

private:
    std::shared_ptr<ImGuiBackend> backend_;

    // Renderer objects
    renderer::RenderState renderState_;
    std::shared_ptr<renderer::Pipeline> pipeline_;
    std::shared_ptr<renderer::Texture2D> fontsTexture_;
    std::shared_ptr<renderer::TextureSampler> fontsTextureSampler_;
    std::shared_ptr<renderer::VertexArray> vertexArray_;

    // TMP; copy into vao
    std::shared_ptr<renderer::VertexBuffer> vertexBuffer_;

    std::vector<ImGuiRenderable> renderables_;
};

}  // namespace imgui
}  // namespace glbr