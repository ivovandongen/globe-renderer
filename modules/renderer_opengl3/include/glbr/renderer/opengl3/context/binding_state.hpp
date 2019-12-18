#pragma once

#include <glbr/renderer/opengl3/textures/active_texture_opengl3.hpp>

#include <memory>
#include <type_traits>

namespace glbr {
namespace renderer {
namespace opengl3 {

template <class T>
struct BindingOp {};

template <class T>
class BindingState {
public:
    BindingState& operator=(const std::shared_ptr<T>& val) {
        if ((!current_ && !val) || (!current_ || !val || *current_ != *val)) {
            BindingOp<T>::Apply(val);
            current_ = val;
        }

        return *this;
    }

    T& operator*() { return *current_; }
    T* operator->() { return current_.get(); }

private:
    std::shared_ptr<T> current_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr