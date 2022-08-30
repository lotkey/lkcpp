#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_rvalue_reference : public lkcpp::false_type {};

template<class T>
struct is_rvalue_reference<T const> : public is_rvalue_reference<T> {};

template<class T>
struct is_rvalue_reference<T&&> : public lkcpp::true_type {};
} // namespace lkcpp