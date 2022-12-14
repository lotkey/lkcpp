////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/memory/memcpy.hpp"

namespace lkcpp {
template<class T>
void memfill(T* dest, T const& value, lkcpp::size_t count);
void memfill(void* dest, char value, lkcpp::size_t count);

/// Fills a range with some value
/// Modeled after std::memset
/// @param dest Destination to start filling
/// @param value Value to fill the range with
/// @param count Length of range to fill
template<class T>
void memfill(T* dest, T const& value, lkcpp::size_t count)
{
  for (lkcpp::size_t i = 0; i < count; i++) {
    lkcpp::memcpy(dest + i, &value, 1);
  }
}
} // namespace lkcpp