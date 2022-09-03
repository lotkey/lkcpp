#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_trivially_copyable :
    lkcpp::bool_constant<__is_trivially_copyable(T)> {};

template<class T>
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;
} // namespace lkcpp