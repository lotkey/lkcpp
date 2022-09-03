#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_function.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_member_function_pointer : lkcpp::false_type {};

template<class T, class U>
struct _is_member_function_pointer<T U::*> : lkcpp::is_function<T> {};
} // namespace

template<class T>
struct is_member_function_pointer :
    public _is_member_function_pointer<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_member_function_pointer_v =
  is_member_function_pointer<T>::value;
} // namespace lkcpp