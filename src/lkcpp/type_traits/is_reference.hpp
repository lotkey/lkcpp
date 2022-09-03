#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_lvalue_reference.hpp"
#include "lkcpp/type_traits/is_rvalue_reference.hpp"

namespace lkcpp {
template<class T>
struct is_reference :
    lkcpp::bool_constant<lkcpp::is_lvalue_reference_v<T> ||
                         lkcpp::is_rvalue_reference_v<T>> {};

template<class T>
inline constexpr bool is_reference_v = is_reference<T>::value;
} // namespace lkcpp