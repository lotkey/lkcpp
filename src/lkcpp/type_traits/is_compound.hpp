#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_fundamental.hpp"

namespace lkcpp {
template<class T>
struct is_compound :
    public lkcpp::bool_constant<!lkcpp::is_fundamental_v<T>> {};

template<class T>
inline constexpr bool is_compound_v = is_compound<T>::value;
} // namespace lkcpp