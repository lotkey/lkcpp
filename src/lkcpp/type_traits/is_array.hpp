#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_array : public lkcpp::false_type {};

template<class T>
struct _is_array<T[]> : public lkcpp::true_type {};

template<class T, auto Size>
struct _is_array<T[Size]> : public lkcpp::true_type {};
} // namespace

template<class T>
struct is_array : public _is_array<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_array_v = is_array<T>::value;
} // namespace lkcpp