#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/renderer/opengl3/pipeline_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture2d_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture_sampler_opengl3.hpp>
#include <glbr/renderer/shaders/auto_uniforms/builtin_draw_auto_uniforms.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

DeviceOpenGL3 &DeviceOpenGL3::Instance() {
    static DeviceOpenGL3 INSTANCE{};
    return INSTANCE;
}

std::unique_ptr<Pipeline> DeviceOpenGL3::createPipeline(const std::string &vertexSource,
                                                        const std::string &fragmentSource) const {
    return std::make_unique<PipelineOpenGL3>(vertexSource, fragmentSource);
}

DeviceOpenGL3::DeviceOpenGL3() {
    // Register draw auto factories
    drawAutoUniformFactories_["bltin_model"] = std::make_unique<ModelMatrixDrawAutoFactory>();
    drawAutoUniformFactories_["bltin_view"] = std::make_unique<ViewMatrixDrawAutoFactory>();
    drawAutoUniformFactories_["bltin_projection"] = std::make_unique<ProjectionMatrixDrawAutoFactory>();
    drawAutoUniformFactories_["bltin_modelViewProjection"] =
        std::make_unique<ModelViewProjectionMatrixDrawAutoFactory>();
}

std::unique_ptr<Texture2D> DeviceOpenGL3::createTexture2D(Texture2DDescription description,
                                                          TextureTarget target) const {
    return std::make_unique<Texture2DOpenGL3>(description, target);
}

std::unique_ptr<Texture2D> DeviceOpenGL3::createTexture2D(const core::Image &image, bool generateMipmaps) const {
    return std::make_unique<Texture2DOpenGL3>(
        Texture2DDescription{image.width(), image.height(), TextureFormatFromImage(image), generateMipmaps},
        TextureTarget::Texture2D);
}

std::unique_ptr<Texture2D> DeviceOpenGL3::createTexture2D(core::Image &&image, bool generateMipmaps) const {
    return std::make_unique<Texture2DOpenGL3WithImageData>(std::move(image), TextureTarget::Texture2D, generateMipmaps);
}

std::unique_ptr<TextureSampler> DeviceOpenGL3::createTextureSampler(TextureMinificationFilter min,
                                                                    TextureMagnificationFilter mag,
                                                                    TextureWrap s,
                                                                    TextureWrap t) const {
    return std::make_unique<TextureSamplerOpenGL3>(min, mag, s, t);
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr