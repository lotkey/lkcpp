#pragma once

#include <type_traits>

namespace lkcpp {
template<class T>
std::enable_if_t<std::is_fundamental_v<T>> swap(T& t1, T& t2)
{
  T tmp = t1;
  t1 = t2;
  t2 = tmp;
}

template<class T>
std::enable_if_t<!std::is_fundamental_v<T> && std::is_pointer_v<T>> swap(T& t1,
                                                                         T& t2)
{
  T tmp = t1;
  t1 = t2;
  t2 = tmp;
}

template<class T>
std::enable_if_t<!std::is_fundamental_v<T> && !std::is_pointer_v<T>> swap(T& t1,
                                                                          T& t2)
{
  t1.swap(t2);
}
} // namespace lkcpp