#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_pointer : public lkcpp::false_type {};

template<class T>
struct is_pointer<T const> : public is_pointer<T> {};

template<class T>
struct is_pointer<T*> : public lkcpp::true_type {};
} // namespace lkcpp