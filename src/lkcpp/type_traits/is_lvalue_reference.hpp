#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_lvalue_reference : public lkcpp::false_type {};

template<class T>
struct is_lvalue_reference<T const> : public is_lvalue_reference<T> {};

template<class T>
struct is_lvalue_reference<T&> : public lkcpp::true_type {};

template<class T>
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
} // namespace lkcpp