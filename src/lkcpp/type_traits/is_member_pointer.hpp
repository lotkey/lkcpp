#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_member_pointer : lkcpp::false_type {};

template<class T, class U>
struct is_member_pointer<T U::*> : lkcpp::true_type {};

template<class T, class U>
struct is_member_pointer<T const U::*> : lkcpp::true_type {};

template<class T, class U>
struct is_member_pointer<T volatile U::*> : lkcpp::true_type {};

template<class T, class U>
struct is_member_pointer<T const volatile U::*> : lkcpp::true_type {};

template<class T>
inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;
} // namespace lkcpp