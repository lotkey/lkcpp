#pragma once

#include "lkcpp/def.hpp"

namespace lkcpp {
template<class T>
int memcmp(T const* p1, T const* p2, lkcpp::size_t size)
{
  return lkcpp::memcmp(static_cast<void const*>(p1),
                       static_cast<void const*>(p2),
                       size * sizeof(T));
}

template<>
int memcmp(void const* p1, void const* p2, lkcpp::size_t size);
template<>
int memcmp(char const* p1, char const* p2, lkcpp::size_t size);
} // namespace lkcpp