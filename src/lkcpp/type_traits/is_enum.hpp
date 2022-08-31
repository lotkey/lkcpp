#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_enum : public lkcpp::bool_constant<__is_enum(T)> {};

template<class T>
inline constexpr bool is_enum_v = is_enum<T>::value;
} // namespace lkcpp