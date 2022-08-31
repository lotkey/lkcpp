#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_floating_point.hpp"
#include "lkcpp/type_traits/is_integral.hpp"

namespace lkcpp {
template<class T>
struct is_arithmetic :
    public lkcpp::bool_constant<lkcpp::is_integral_v<T> ||
                                lkcpp::is_floating_point_v<T>> {};

template<class T>
inline constexpr bool is_arithmetic_v = lkcpp::is_arithmetic<T>::value;
} // namespace lkcpp