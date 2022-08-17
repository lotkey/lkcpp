#pragma once

#include "lkcpp/def.hpp"

namespace lkcpp {
template<class T>
void memlshift(T* buffer, lkcpp::size_t buffer_size, lkcpp::size_t num_shifts)
{
  memlshift<void>(static_cast<void*>(buffer),
                  buffer_size * sizeof(T),
                  num_shifts * sizeof(T));
}

template<class T>
void memrshift(T* buffer, lkcpp::size_t buffer_size, lkcpp::size_t num_shifts)
{
  memrshift<void>(static_cast<void*>(buffer),
                  buffer_size * sizeof(T),
                  num_shifts * sizeof(T));
}

template<>
void memlshift(void* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts);
template<>
void memlshift(char* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts);
template<>
void memrshift(void* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts);
template<>
void memrshift(char* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts);
} // namespace lkcpp