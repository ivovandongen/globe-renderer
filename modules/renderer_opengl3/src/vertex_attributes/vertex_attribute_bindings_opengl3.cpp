#include <glbr/renderer/opengl3/vertex_attributes/vertex_attribute_bindings_opengl3.hpp>

#include <glad/glad.h>
#include <glbr/renderer/opengl3/errors.hpp>

namespace {

GLenum convert(glbr::renderer::VertexAttribute::Type type) {
    using namespace glbr::renderer;
    switch (type) {
        case VertexAttribute::Type::Float:
            return GL_FLOAT;
    }
}

}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

void VertexAttributeBindingsOpenGL3::clean(const std::vector<ShaderVertexAttribute>& shaderAttributes) {
    if (_dirty) {
        for (auto& binding : _attributes) {
            auto& attrib = binding.second;
            auto type = convert(attrib.type());
            auto location = std::find_if(std::cbegin(shaderAttributes), std::cend(shaderAttributes),
                                         [&](auto& val) { return val.name() == binding.first; });

            if (location == std::end(shaderAttributes)) {
                // TODO log this properly
                std::cerr << "No shader vertex attribute found for key: " << binding.first << std::endl;
                continue;
            }

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