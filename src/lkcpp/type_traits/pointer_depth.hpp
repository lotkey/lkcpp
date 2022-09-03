#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/type_traits/integral_constant.hpp"
#include "lkcpp/type_traits/remove_cv.hpp"

namespace lkcpp {
namespace {
template<class T>
struct _pointer_depth : public lkcpp::integral_constant<lkcpp::size_t, 0> {};

template<class T>
struct _pointer_depth<T*> :
    public lkcpp::integral_constant<lkcpp::size_t,
                                    1 + _pointer_depth<T>::value> {};
} // namespace

template<class T>
struct pointer_depth : public _pointer_depth<lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr lkcpp::size_t pointer_depth_v = pointer_depth<T>::value;
} // namespace lkcpp