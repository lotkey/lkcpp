#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_floating_point : public lkcpp::false_type {};

template<class T>
struct is_floating_point<T const> : public is_floating_point<T> {};

template<>
struct is_floating_point<float> : public lkcpp::true_type {};

template<>
struct is_floating_point<double> : public lkcpp::true_type {};

template<>
struct is_floating_point<long double> : public lkcpp::true_type {};
} // namespace lkcpp