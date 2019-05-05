#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/renderer/opengl3/pipeline_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

DeviceOpenGL3 &DeviceOpenGL3::instance() {
    static DeviceOpenGL3 INSTANCE{};
    return INSTANCE;
}

std::unique_ptr<Pipeline> DeviceOpenGL3::createPipeline(const std::string &vertexSource,
                                                        const std::string &fragmentSource) {
    return std::make_unique<PipelineOpenGL3>(vertexSource, fragmentSource);
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr