#pragma once

#include <mapbox/variant.hpp>

namespace glbr {
namespace core {

template <class... T>
using variant = mapbox::util::variant<T...>;

template <class F, class V>
inline auto apply_visitor(F&& f, V const& v) {
    return mapbox::util::apply_visitor(f, v);
}

template <class F, class V>
inline auto apply_visitor(F&& f, V& v) {
    return mapbox::util::apply_visitor(f, v);
}

template <class ResultType, class T>
auto get(T& var) {
    return mapbox::util::get<ResultType>(var);
}

template <class ResultType, class T>
auto get(const T& var) {
    return mapbox::util::get<ResultType>(var);
}

}  // namespace core
}  // namespace glbr