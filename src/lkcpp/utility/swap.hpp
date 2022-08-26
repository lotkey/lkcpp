////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/memory/alloc.hpp"
#include "lkcpp/memory/memcpy.hpp"
#include "lkcpp/object.hpp"

#include <type_traits>

namespace lkcpp {
template<class T>
class custom_swap {
public:
  virtual void swap(T& t) = 0;
};

template<class T>
std::enable_if_t<std::is_base_of_v<custom_swap<T>, T>> swap(T& t1, T& t2)
{
  t1.swap(t2);
}

template<class T>
std::enable_if_t<!std::is_base_of_v<custom_swap<T>, T>> swap(T& t1, T& t2)
{
  if (lkcpp::is(t1, t2)) { return; }
  T* tmp = lkcpp::alloc<T>();
  lkcpp::memcpy(tmp, &t1, 1);
  lkcpp::memcpy(&t1, &t2, 1);
  lkcpp::memcpy(&t2, tmp, 1);
  lkcpp::dealloc(tmp);
}
} // namespace lkcpp