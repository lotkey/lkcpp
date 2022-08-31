#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_const.hpp"
#include "lkcpp/type_traits/is_reference.hpp"

namespace lkcpp {
template<class T>
struct is_function :
    lkcpp::bool_constant<!lkcpp::is_const<const T>::value &&
                         !lkcpp::is_reference<T>::value> {};

template<class T>
inline constexpr bool is_function_v = is_function<T>::value;
} // namespace