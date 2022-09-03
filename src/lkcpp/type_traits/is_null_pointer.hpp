#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_null_pointer : public lkcpp::false_type {};

template<>
struct _is_null_pointer<lkcpp::nullptr_t> : public lkcpp::true_type {};
} // namespace

template<class T>
struct is_null_pointer : public _is_null_pointer<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
} // namespace lkcpp