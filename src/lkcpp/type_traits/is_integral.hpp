#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_integral : public lkcpp::false_type {};

template<>
struct _is_integral<bool> : public lkcpp::true_type {};

template<>
struct _is_integral<char> : public lkcpp::true_type {};

template<>
struct _is_integral<unsigned char> : public lkcpp::true_type {};

template<>
struct _is_integral<signed char> : public lkcpp::true_type {};

template<>
struct _is_integral<int> : public lkcpp::true_type {};

template<>
struct _is_integral<unsigned int> : public lkcpp::true_type {};

template<>
struct _is_integral<short int> : public lkcpp::true_type {};

template<>
struct _is_integral<unsigned short int> : public lkcpp::true_type {};

template<>
struct _is_integral<long int> : public lkcpp::true_type {};

template<>
struct _is_integral<unsigned long int> : public lkcpp::true_type {};

template<>
struct _is_integral<long long int> : public lkcpp::true_type {};

template<>
struct _is_integral<unsigned long long int> : public lkcpp::true_type {};

template<>
struct _is_integral<wchar_t> : public lkcpp::true_type {};
} // namespace

template<class T>
struct is_integral : public _is_integral<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_integral_v = is_integral<T>::value;
} // namespace lkcpp