#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_arithmetic.hpp"
#include "lkcpp/type_traits/is_enum.hpp"
#include "lkcpp/type_traits/is_member_pointer.hpp"
#include "lkcpp/type_traits/is_null_pointer.hpp"
#include "lkcpp/type_traits/is_pointer.hpp"

namespace lkcpp {
template<class T>
struct is_scalar :
    lkcpp::bool_constant<lkcpp::is_arithmetic_v<T> || lkcpp::is_enum_v<T> ||
                         lkcpp::is_member_pointer_v<T> ||
                         lkcpp::is_null_pointer_v<T> ||
                         lkcpp::is_pointer_v<T>> {};

template<class T>
inline constexpr bool is_scalar_v = is_scalar<T>::value;
} // namespace lkcpp