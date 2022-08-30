#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct array_depth : public lkcpp::integral_constant<lkcpp::size_t, 0> {};

template<class T>
struct array_depth<T const[]> : public array_depth<T[]> {};

template<class T, lkcpp::size_t Size>
struct array_depth<T const[Size]> : public array_depth<T[Size]> {};

template<class T>
struct array_depth<T[]> :
    public lkcpp::integral_constant<lkcpp::size_t, 1 + array_depth<T>::value> {
};

template<class T, lkcpp::size_t Size>
struct array_depth<T[Size]> :
    public lkcpp::integral_constant<lkcpp::size_t, 1 + array_depth<T>::value> {
};

template<class T>
inline constexpr lkcpp::size_t array_depth_v = array_depth<T>::value;
} // namespace lkcpp