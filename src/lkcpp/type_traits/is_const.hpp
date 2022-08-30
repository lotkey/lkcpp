#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_const : public lkcpp::false_type {};

template<class T>
struct is_const<T const> : public lkcpp::true_type {};

template<class T>
inline constexpr bool is_const_v = is_const<T>::value;
} // namespace lkcpp