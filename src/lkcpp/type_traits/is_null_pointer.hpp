#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_null_pointer : public lkcpp::false_type {};

template<class T>
struct is_null_pointer<T const> : public is_null_pointer<T> {};

template<>
struct is_null_pointer<lkcpp::nullptr_t> : public lkcpp::true_type {};
} // namespace lkcpp