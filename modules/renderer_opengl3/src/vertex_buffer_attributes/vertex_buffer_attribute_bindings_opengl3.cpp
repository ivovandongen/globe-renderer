#include <glbr/renderer/opengl3/vertex_buffer_attributes/vertex_buffer_attribute_bindings_opengl3.hpp>

#include <glbr/logging/logging.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

#include <glad/glad.h>

#include <algorithm>

namespace {

GLenum convert(glbr::renderer::VertexBufferAttribute::Type type) {
    using namespace glbr::renderer;
    switch (type) {
        case VertexBufferAttribute::Type::Float:
            return GL_FLOAT;
    }
}

}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

void VertexBufferAttributeBindingsOpenGL3::clean(const std::vector<ShaderVertexAttribute>& shaderAttributes) {
    if (_dirty) {
        for (auto& binding : _attributes) {
            auto& attrib = binding.second;
            auto type = convert(attrib.type());
            auto location = std::find_if(std::cbegin(shaderAttributes), std::cend(shaderAttributes),
                                         [&](auto& val) { return val.name() == binding.first; });

            if (location == std::end(shaderAttributes)) {
                logging::error("No shader vertex attribute found for key: {}", binding.first);
                continue;
            }

            // Bind the vertex buffer
            attrib.buffer().bind();

            logging::debug(
                "Binding vertex attribute {} at position {} (components: {}, type: {}, normalize: {}, stride: {}, "
                "offset: {})",
                binding.first, location->location(), attrib.components(), type, attrib.normalize(), attrib.stride(),
                attrib.offset());

            GL_VERIFY(glVertexAttribPointer(location->location(), attrib.components(), type, attrib.normalize(),
                                            attrib.stride(), reinterpret_cast<void*>(attrib.offset())));
            GL_VERIFY(glEnableVertexAttribArray(location->location()));
        }
        _dirty = false;
    }
}
}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr