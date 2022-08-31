#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/is_union.hpp"

namespace lkcpp {
namespace {
template<class T>
lkcpp::integral_constant<bool, !lkcpp::is_union<T>::value> test(int T::*);

template<class>
lkcpp::false_type test(...);
} // namespace

template<class T>
struct is_class : decltype(test<T>(nullptr)) {};

template <class T>
inline constexpr bool is_class_v = is_class<T>::value;
} // namespace lkcpp