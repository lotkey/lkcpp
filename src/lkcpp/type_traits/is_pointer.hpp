#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_pointer : public lkcpp::false_type {};

template<class T>
struct _is_pointer<T*> : public lkcpp::true_type {};
} // namespace

template<class T>
struct is_pointer : public _is_pointer<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;
} // namespace lkcpp