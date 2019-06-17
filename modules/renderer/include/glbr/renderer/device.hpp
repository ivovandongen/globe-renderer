#pragma once

#include <glbr/core/image.hpp>
#include <glbr/renderer/pipeline.hpp>
#include <glbr/renderer/textures/texture2d.hpp>
#include <glbr/renderer/textures/texture_format.hpp>
#include <glbr/renderer/textures/texture_magnification_filter.hpp>
#include <glbr/renderer/textures/texture_minification_filter.hpp>
#include <glbr/renderer/textures/texture_sampler.hpp>
#include <glbr/renderer/textures/texture_wrap.hpp>

#include <memory>
#include <string>

namespace glbr {
namespace renderer {

class Device {
public:
    virtual ~Device() = default;

    virtual std::unique_ptr<Pipeline> createPipeline(const std::string &vertexSource,
                                                     const std::string &fragmentSource) const = 0;

    virtual std::unique_ptr<Texture2D> createTexture2D(const core::Image &, bool generateMipmaps) const = 0;

    virtual std::unique_ptr<Texture2D> createTexture2D(const core::Image &, TextureFormat format,
                                                       bool generateMipmaps) const = 0;

    virtual std::unique_ptr<TextureSampler> createTextureSampler(TextureMinificationFilter, TextureMagnificationFilter,
                                                                 TextureWrap s, TextureWrap t) const = 0;

protected:
    Device() = default;
};

}  // namespace renderer
}  // namespace glbr