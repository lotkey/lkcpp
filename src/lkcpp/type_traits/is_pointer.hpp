#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_pointer : public lkcpp::false_type {};

template<class T>
struct is_pointer<T*> : public lkcpp::true_type {};

template<class T>
struct is_pointer<T* const> : public lkcpp::true_type {};

template<class T>
struct is_pointer<T* volatile> : public lkcpp::true_type {};

template<class T>
struct is_pointer<T* const volatile> : public lkcpp::true_type {};

template<class T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;
} // namespace lkcpp