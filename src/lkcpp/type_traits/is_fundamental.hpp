#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_arithmetic.hpp"
#include "lkcpp/type_traits/is_same.hpp"
#include "lkcpp/type_traits/is_void.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
template<class T>
struct is_fundamental :
    public lkcpp::bool_constant<
      lkcpp::is_arithmetic_v<T> || lkcpp::is_void_v<T> ||
      lkcpp::is_same_v<lkcpp::nullptr_t, lkcpp::remove_cv_t<T>>> {};

template<class T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;
} // namespace lkcpp