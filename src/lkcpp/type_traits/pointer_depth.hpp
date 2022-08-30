#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/type_traits/integral_constant.hpp"

namespace lkcpp {
template<class T>
struct pointer_depth : public lkcpp::integral_constant<lkcpp::size_t, 0> {};

template<class T>
struct pointer_depth<T const> : public pointer_depth<T> {};

template<class T>
struct pointer_depth<T*> :
    public lkcpp::integral_constant<lkcpp::size_t,
                                    1 + pointer_depth<T>::value> {};

template<class T>
inline constexpr lkcpp::size_t pointer_depth_v = pointer_depth<T>::value;
} // namespace lkcpp