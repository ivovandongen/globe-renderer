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

    void addRenderable(const ImGuiRenderable& renderable) { _renderables.push_back(renderable); }

    void init(renderer::Context& context) override;

    void render(renderer::Context& context, renderer::SceneState& sceneState) override;

private:
    void renderDrawData(renderer::Context& context, const renderer::SceneState& sceneState, ImDrawData* drawData);

private:
    std::shared_ptr<ImGuiBackend> _backend;

    // Renderer objects
    renderer::RenderState _renderState;
    std::shared_ptr<renderer::Pipeline> _pipeline;
    std::shared_ptr<renderer::Texture2D> _fontsTexture;
    std::shared_ptr<renderer::TextureSampler> _fontsTextureSampler;
    std::shared_ptr<renderer::VertexArray> _vertexArray;

    // TMP; copy into vao
    std::shared_ptr<renderer::VertexBuffer> _vertexBuffer;

    std::vector<ImGuiRenderable> _renderables;
};

}  // namespace imgui
}  // namespace glbr