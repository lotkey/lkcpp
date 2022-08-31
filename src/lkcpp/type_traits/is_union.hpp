#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_union : public lkcpp::bool_constant<__is_union(T)> {};

template<class T>
inline constexpr bool is_union_v = is_union<T>::value;
} // namespace lkcpp