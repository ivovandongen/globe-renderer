#pragma once

#include <renderer/pipeline.hpp>

#include <memory>
#include <string>

namespace renderer {

class Device {
public:

    virtual ~Device() = default;

    virtual std::unique_ptr<Pipeline> createPipeline(const std::string &vertexSource, const std::string &fragmentSource) = 0;

protected:
    Device() = default;
};

} // namespace renderer