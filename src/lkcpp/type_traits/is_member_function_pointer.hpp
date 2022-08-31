#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_function.hpp"

namespace lkcpp {
template<class T>
struct is_member_function_pointer : lkcpp::false_type {};

template<class T, class U>
struct is_member_function_pointer<T U::*> : lkcpp::is_function<T> {};

template<class T, class U>
struct is_member_function_pointer<T const U::*> : lkcpp::is_function<T> {};

template<class T, class U>
struct is_member_function_pointer<T volatile U::*> : lkcpp::is_function<T> {};

template<class T, class U>
struct is_member_function_pointer<T const volatile U::*> :
    lkcpp::is_function<T> {};

template<class T>
inline constexpr bool is_member_function_pointer_v =
  is_member_function_pointer<T>::value;
} // namespace lkcpp