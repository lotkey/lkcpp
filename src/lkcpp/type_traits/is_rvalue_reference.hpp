#pragma once

#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _is_rvalue_reference : public lkcpp::false_type {};

template<class T>
struct _is_rvalue_reference<T&&> : public lkcpp::true_type {};
} // namespace

template<class T>
struct is_rvalue_reference :
    public _is_rvalue_reference<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
} // namespace lkcpp