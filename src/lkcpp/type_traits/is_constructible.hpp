#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_constructible : public lkcpp::bool_constant<__is_constructible(T)> {};

template<class T>
inline constexpr bool is_constructible_v = is_constructible<T>::value;
} // namespace lkcpp