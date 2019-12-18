#pragma once

#include <tl/expected.hpp>

namespace glbr {
namespace core {

template <class T, class E>
using expected = tl::expected<T, E>;

}  // namespace core
}  // namespace glbr