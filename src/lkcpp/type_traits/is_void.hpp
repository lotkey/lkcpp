#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_void : public lkcpp::false_type {};

template<class T>
struct is_void<T const> : public is_void<T> {};

template<>
struct is_void<void> : public lkcpp::true_type {};
} // namespace lkcpp