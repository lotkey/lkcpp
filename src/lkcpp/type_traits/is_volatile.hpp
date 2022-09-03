#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_volatile : lkcpp::false_type {};

template<class T>
struct is_volatile<T volatile> : lkcpp::true_type {};

template<class T>
inline constexpr bool is_volatile_v = is_volatile<T>::value;
} // namespace lkcpp