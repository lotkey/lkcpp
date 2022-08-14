////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"

namespace lkcpp {
template<class T>
void memcpy(T* dest, T const* source, size_t count);
template<>
void memcpy(void* dest, void const* source, size_t num_bytes);
template<>
void memcpy(char* dest, char const* source, size_t num_bytes);

/// Copies memory from source to dest, even if they are overlapping
/// Modeled after std::memcpy std::memmove
/// @param dest Destination to copy memory to
/// @param source Source to copy memory from. This will be overwritten if the
/// regions overlap.
/// @param count Number of elements to copy
template<class T>
inline void memcpy(T* dest, T const* source, size_t count)
{
  lkcpp::memcpy(static_cast<void*>(dest),
                static_cast<void const*>(source),
                count * sizeof(T));
}
} // namespace lkcpp