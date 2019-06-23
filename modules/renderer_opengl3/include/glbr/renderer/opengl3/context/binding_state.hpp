#pragma once

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
        if ((!current && !val) || (!current || !val || *current != *val)) {
            BindingOp<T>::Apply(val);
            current = val;
        }

        return *this;
    }

    T& operator*() { return *current; }
    T* operator->() { return current.get(); }

private:
    std::shared_ptr<T> current;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr