#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_member_pointer : lkcpp::false_type {};

template<class T, class U>
struct _is_member_pointer<T U::*> : lkcpp::true_type {};
} // namespace

template<class T>
struct is_member_pointer : public _is_member_pointer<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;
} // namespace lkcpp