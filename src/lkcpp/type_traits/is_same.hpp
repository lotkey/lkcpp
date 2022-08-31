#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T, class U>
struct is_same : public lkcpp::false_type {};

template<class T>
struct is_same<T, T> : public lkcpp::true_type {};

template<class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;
} // namespace lkcpp