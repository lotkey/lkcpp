#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_floating_point : public lkcpp::false_type {};

template<>
struct _is_floating_point<float> : public lkcpp::true_type {};

template<>
struct _is_floating_point<double> : public lkcpp::true_type {};

template<>
struct _is_floating_point<long double> : public lkcpp::true_type {};
} // namespace

template<class T>
struct is_floating_point : public _is_floating_point<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;
} // namespace lkcpp