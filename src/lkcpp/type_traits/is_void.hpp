#pragma once

#include "lkcpp/type_traits/is_same.hpp"

namespace lkcpp {
template<class T>
struct is_void : public lkcpp::is_same<void, lkcpp::remove_cv_t<T>> {};

template<class T>
inline constexpr bool is_void_v = is_void<T>::value;
} // namespace lkcpp