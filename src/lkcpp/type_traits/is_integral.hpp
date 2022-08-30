#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct is_integral : public lkcpp::false_type {};

template<class T>
struct is_integral<T const> : public is_integral<T> {};

template<>
struct is_integral<char> : public lkcpp::true_type {};

template<>
struct is_integral<unsigned char> : public lkcpp::true_type {};

template<>
struct is_integral<signed char> : public lkcpp::true_type {};

template<>
struct is_integral<int> : public lkcpp::true_type {};

template<>
struct is_integral<unsigned int> : public lkcpp::true_type {};

template<>
struct is_integral<short int> : public lkcpp::true_type {};

template<>
struct is_integral<unsigned short int> : public lkcpp::true_type {};

template<>
struct is_integral<long int> : public lkcpp::true_type {};

template<>
struct is_integral<unsigned long int> : public lkcpp::true_type {};

template<>
struct is_integral<long long int> : public lkcpp::true_type {};

template<>
struct is_integral<unsigned long long int> : public lkcpp::true_type {};

template<>
struct is_integral<wchar_t> : public lkcpp::true_type {};

template<class T>
inline constexpr bool is_integral_v = is_integral<T>::value;
} // namespace lkcpp