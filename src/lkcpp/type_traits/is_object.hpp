#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_array.hpp"
#include "lkcpp/type_traits/is_class.hpp"
#include "lkcpp/type_traits/is_scalar.hpp"
#include "lkcpp/type_traits/is_union.hpp"

namespace lkcpp {
template<class T>
struct is_object :
    public lkcpp::bool_constant<lkcpp::is_array_v<T> || lkcpp::is_class_v<T> ||
                                lkcpp::is_scalar_v<T> || lkcpp::is_union_v<T>> {
};

template<class T>
inline constexpr bool is_object_v = is_object<T>::value;
} // namespace lkcpp