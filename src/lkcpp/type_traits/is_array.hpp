#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_array : public lkcpp::false_type {};

template<class T>
struct is_array<T[]> : public lkcpp::true_type {};

template<class T>
struct is_array<T const[]> : public lkcpp::true_type {};

template<class T, auto Size>
struct is_array<T[Size]> : public lkcpp::true_type {};

template<class T, auto Size>
struct is_array<T const[Size]> : public lkcpp::true_type {};

template<class T>
inline constexpr bool is_array_v = is_array<T>::value;
} // namespace lkcpp