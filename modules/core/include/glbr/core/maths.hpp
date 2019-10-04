#pragma once

#include <cmath>

namespace glbr {
namespace core {

template <class T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
inline T deg2rad(T deg) {
    return deg * M_PI / T(180);
};

template <class T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
inline T rad2deg(T deg) {
    return deg * T(180) / M_PI;
};

}  // namespace core
}  // namespace glbr