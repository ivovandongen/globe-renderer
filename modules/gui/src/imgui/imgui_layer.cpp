#include <glbr/imgui/imgui_layer.hpp>

#include <glbr/imgui/imgui_backend.hpp>

#include <imgui.h>

namespace glbr {
namespace imgui {

static const constexpr char* VERTEX_SRC = R"(
    #version 330 core

    layout (location = 0) in vec2 Position;
    layout (location = 1) in vec2 UV;
    layout (location = 2) in vec4 Color;
    uniform mat4 ProjMtx;
    out vec2 Frag_UV;
    out vec4 Frag_Color;

    void main() {
        Frag_UV = UV;
        Frag_Color = Color;
        gl_Position = ProjMtx * vec4(Position.xy,0,1);
    }
)";

static const constexpr char* FRAGMENT_SRC = R"(
    #version 330 core

    in vec2 Frag_UV;
    in vec4 Frag_Color;
    uniform sampler2D Texture;
    layout (location = 0) out vec4 Out_Color;

    void main() {
        Out_Color = Frag_Color * texture(Texture, Frag_UV.st);
    }
)";

using namespace renderer;

void ImGuiLayer::renderDrawData(Context& context, const SceneState& sceneState, ImDrawData* drawData) {
    using namespace glbr::renderer;

    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer
    // coordinates)
    int fbWidth = int(drawData->DisplaySize.x * drawData->FramebufferScale.x);
    int fbHeight = int(drawData->DisplaySize.y * drawData->FramebufferScale.y);
    if (fbWidth <= 0 || fbHeight <= 0) {
        return;
    }

    // Setup viewport, orthographic projection matrix
    // Our visible imgui space lies from draw_data->DisplayPos (top left) to
    // draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    float L = drawData->DisplayPos.x;
    float R = drawData->DisplayPos.x + drawData->DisplaySize.x;
    float T = drawData->DisplayPos.y;
    float B = drawData->DisplayPos.y + drawData->DisplaySize.y;
    glm::mat4 orthoProjection = {
        {2.0f / (R - L), 0.0f, 0.0f, 0.0f},
        {0.0f, 2.0f / (T - B), 0.0f, 0.0f},
        {0.0f, 0.0f, -1.0f, 0.0f},
        {(R + L) / (L - R), (T + B) / (B - T), 0.0f, 1.0f},
    };

    pipeline_->uniforms()["ProjMtx"] = orthoProjection;

    // Setup texture unit
    context.textureUnits()[0].sampler(fontsTextureSampler_);
    context.textureUnits()[0].texture(fontsTexture_);
    pipeline_->uniforms()["Texture"] = 0;

    // Will project scissor/clipping rectangles into framebuffer space
    ImVec2 clipOff = drawData->DisplayPos;          // (0,0) unless using multi-viewports
    ImVec2 clipScale = drawData->FramebufferScale;  // (1,1) unless using retina display which are often (2,2)

    // Bind the vertex array
    vertexArray_->bind();

    // TODO: this should not be necessary, if we did not postpone attribute binding
    vertexBuffer_->bind();

    // Render command lists
    for (int n = 0; n < drawData->CmdListsCount; n++) {
        const ImDrawList* cmdList = drawData->CmdLists[n];

        // Upload vertex/index buffers
        vertexBuffer_->upload(cmdList->VtxBuffer.Data, cmdList->VtxBuffer.Size * sizeof(ImDrawVert));
        vertexArray_->indexBuffer()->upload(cmdList->IdxBuffer.Data, cmdList->IdxBuffer.Size);

        for (int cmd_i = 0; cmd_i < cmdList->CmdBuffer.Size; cmd_i++) {
            const ImDrawCmd* pcmd = &cmdList->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != nullptr) {
                // User callback, registered via ImDrawList::AddCallback()
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) {
                    // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the
                    // renderer to reset render state.)
                    // NOOP
                    logging::warn("Render reset requested in imgui render");
                } else {
                    logging::debug("User callback requested in imgui render");
                    pcmd->UserCallback(cmdList, pcmd);
                }
            } else {
                // Project scissor/clipping rectangles into framebuffer space
                Rectangle clipRect{static_cast<int>((pcmd->ClipRect.x - clipOff.x) * clipScale.x),
                                   static_cast<int>((pcmd->ClipRect.y - clipOff.y) * clipScale.y),
                                   static_cast<int>((pcmd->ClipRect.z - clipOff.x) * clipScale.x),
                                   static_cast<int>((pcmd->ClipRect.w - clipOff.y) * clipScale.y)};

                if (clipRect.x < fbWidth && clipRect.y < fbHeight && clipRect.width >= 0.0f &&
                    clipRect.height >= 0.0f) {
                    // Apply scissor/clipping rectangle
                    renderState_.scissorTest.rectangle = clipRect;

                    DrawState drawState{renderState_, pipeline_, vertexArray_};

                    context.draw(core::geometry::PrimitiveType::TRIANGLES,
                                 drawState,
                                 sceneState,
                                 pcmd->IdxOffset * sizeof(ImDrawIdx));
                }
            }
        }
    }
}

static std::shared_ptr<Texture2D> createFontsTexture(const Context& context) {
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small)
    // because it is more likely to be compatible with user's existing shaders. If your
    // ImTextureId represent a higher-level concept than just a GL texture id, consider
    // calling GetTexDataAsAlpha8() instead to save on GPU memory.
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    auto fontsTexture =
        context.device().createTexture2D({width, height, TextureFormat::RGBA32f, false}, TextureTarget::Texture2D);
    fontsTexture->bind();
    fontsTexture->upload(pixels);

    return fontsTexture;
}

ImGuiLayer::ImGuiLayer(core::EventProducer& producer)
    : backend_(ImGuiBackend::Instance(producer)){

      };

void ImGuiLayer::init(Context& context) {
    pipeline_ = context.device().createPipeline(VERTEX_SRC, FRAGMENT_SRC);

    fontsTexture_ = createFontsTexture(context);
    fontsTextureSampler_ = context.device().createTextureSampler(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);
    fontsTextureSampler_->bind(0);

    vertexArray_ = context.createVertexArray();
    vertexArray_->bind();
    vertexArray_->indexBuffer(context.createIndexBuffer(IndexBufferType::U_SHORT, BufferHint::StreamDraw));
    vertexArray_->indexBuffer()->bind();
    vertexBuffer_ = context.createVertexBuffer(BufferHint::StreamDraw);
    vertexBuffer_->bind();

    // Bind vertex/index buffers and setup attributes for ImDrawVert
    vertexArray_->add("Position", {vertexBuffer_, VertexBufferAttribute::Type::Float, 2, false, sizeof(ImDrawVert), 0});
    vertexArray_->add(
        "UV",
        {vertexBuffer_, VertexBufferAttribute::Type::Float, 2, false, sizeof(ImDrawVert), offsetof(ImDrawVert, uv)});
    vertexArray_->add("Color",
                      {vertexBuffer_,
                       VertexBufferAttribute::Type::UnsignedByte,
                       4,
                       true,
                       sizeof(ImDrawVert),
                       offsetof(ImDrawVert, col)});
    vertexArray_->unbind();

    renderState_.blending.enabled = true;
    renderState_.blending.equation(BlendEquation::ADD);
    renderState_.blending.factor(SourceBlendingFactor::SOURCE_ALPHA);
    renderState_.blending.factor(DestinationBlendingFactor::ONE_MINUS_SOURCE_ALPHA);
    renderState_.faceCulling.enabled = false;
    renderState_.depthTest.enabled = false;
    renderState_.scissorTest.enabled = true;
    renderState_.rasterizationMode = RasterizationMode::FILL;
}

// Keep track of frame rate
static std::chrono::steady_clock::time_point lastRender;

void ImGuiLayer::render(Context& context, SceneState& sceneState) {
    assert(pipeline_);

    auto now = std::chrono::high_resolution_clock::now();
    if (!lastRender.time_since_epoch().count()) {
        lastRender = now;
    }
    auto interval = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastRender);
    auto intervalS = std::chrono::duration_cast<std::chrono::duration<float>>(interval).count();

    auto& io = ImGui::GetIO();
    if (intervalS > 0) {
        io.DeltaTime = intervalS;
    }
    lastRender = now;

    auto viewport = sceneState.viewport();
    io.DisplaySize = {viewport.width, viewport.height};
    auto fbSale = 1.f / sceneState.pixelRatio();
    io.DisplayFramebufferScale = {fbSale, fbSale};

    ImGui::NewFrame();

    for (auto& renderable : renderables_) {
        renderable();
    }

    ImGui::Render();

    renderDrawData(context, sceneState, ImGui::GetDrawData());
}

}  // namespace imgui
}  // namespace glbr
