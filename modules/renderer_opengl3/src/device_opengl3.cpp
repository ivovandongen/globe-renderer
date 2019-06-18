#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/renderer/opengl3/pipeline_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture2d_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture_sampler_opengl3.hpp>
#include <glbr/renderer/shaders/auto_uniforms/builtin_draw_auto_uniforms.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

DeviceOpenGL3 &DeviceOpenGL3::instance() {
    static DeviceOpenGL3 INSTANCE{};
    return INSTANCE;
}

std::unique_ptr<Pipeline> DeviceOpenGL3::createPipeline(const std::string &vertexSource,
                                                        const std::string &fragmentSource) const {
    return std::make_unique<PipelineOpenGL3>(vertexSource, fragmentSource);
}

DeviceOpenGL3::DeviceOpenGL3() {
    // Register draw auto factories
    _drawAutoUniformFactories["bltin_model"] = std::make_unique<ModelMatrixDrawAutoFactory>();
    _drawAutoUniformFactories["bltin_view"] = std::make_unique<ViewMatrixDrawAutoFactory>();
    _drawAutoUniformFactories["bltin_projection"] = std::make_unique<ProjectionMatrixDrawAutoFactory>();
}

std::unique_ptr<Texture2D> DeviceOpenGL3::createTexture2D(const core::Image &image, bool generateMipmaps) const {
    TextureFormat format = [&]() {
        switch (image.channels()) {
            case 1:
                return TextureFormat::R8;
            case 2:
                return TextureFormat::RG8;
            case 4:
                return TextureFormat::RGBA8;
            case 3:
            default:
                return TextureFormat::RGB8;
        }
    }();

    auto texture = std::make_unique<Texture2DOpenGL3>(
        Texture2DDescription{image.width(), image.height(), format, generateMipmaps}, TextureTarget::Texture2D);
    texture->upload(image.data());
    return texture;
}

std::unique_ptr<Texture2D> DeviceOpenGL3::createTexture2D(const core::Image &image, TextureFormat format,
                                                          bool generateMipmaps) const {
    auto texture = std::make_unique<Texture2DOpenGL3>(
        Texture2DDescription{image.width(), image.height(), format, generateMipmaps}, TextureTarget::Texture2D);
    texture->upload(image.data());
    return texture;
}

std::unique_ptr<TextureSampler> DeviceOpenGL3::createTextureSampler(TextureMinificationFilter min,
                                                                    TextureMagnificationFilter mag, TextureWrap s,
                                                                    TextureWrap t) const {
    return std::make_unique<TextureSamplerOpenGL3>(min, mag, s, t);
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr