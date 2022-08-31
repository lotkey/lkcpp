#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_member_function_pointer.hpp"
#include "lkcpp/type_traits/is_member_pointer.hpp"

namespace lkcpp {
template<class T>
struct is_member_object_pointer :
    public lkcpp::bool_constant<lkcpp::is_member_pointer_v<T> &&
                                !lkcpp::is_member_function_pointer_v<T>> {};

template<class T>
inline constexpr bool is_member_object_pointer_v =
  is_member_object_pointer<T>::value;
} // namespace lkcpp