#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_reference : public lkcpp::false_type {};

template<class T>
struct is_reference<T const> : public is_reference<T> {};

template<class T>
struct is_reference<T&> : public lkcpp::true_type {};

template<class T>
struct is_reference<T&&> : public lkcpp::true_type {};
} // namespace lkcpp