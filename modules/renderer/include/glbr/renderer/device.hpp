#pragma once

#include <glbr/renderer/pipeline.hpp>

#include <memory>
#include <string>

namespace glbr {
namespace renderer {

class Device {
public:
    virtual ~Device() = default;

    virtual std::unique_ptr<Pipeline> createPipeline(const std::string &vertexSource,
                                                     const std::string &fragmentSource) = 0;

protected:
    Device() = default;
};

}  // namespace renderer
}  // namespace glbr