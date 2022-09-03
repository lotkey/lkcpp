#pragma once

namespace lkcpp {
template<class T>
struct remove_cv {
  using type = T;
};

template<class T>
struct remove_cv<T const> {
  using type = T;
};

template<class T>
struct remove_cv<T volatile> {
  using type = T;
};

template<class T>
struct remove_cv<T const volatile> {
  using type = T;
};

template<class T>
struct remove_const {
  using type = T;
};

template<class T>
struct remove_const<T const> {
  using type = T;
};

template<class T>
struct remove_volatile {
  using type = T;
};

template<class T>
struct remove_volatile<T volatile> {
  using type = T;
};

template<class T>
using remove_cv_t = typename remove_cv<T>::type;
template<class T>
using remove_const_t = typename remove_const<T>::type;
template<class T>
using remove_volatile_t = typename remove_volatile<T>::type;
} // namespace lkcpp