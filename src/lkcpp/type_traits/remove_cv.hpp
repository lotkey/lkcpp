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
} // namespace lkcpp