#include "lkcpp/memory/memshift.hpp"
#include "lkcpp/memory/alloc.hpp"
#include "lkcpp/memory/memcpy.hpp"

namespace lkcpp {
template<>
void memlshift(void* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts)
{
  memlshift<char>(static_cast<char*>(buffer), buffer_size, num_shifts);
}

template<>
void memlshift(char* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts)
{
  if (buffer_size == 0) { return; }
  num_shifts %= buffer_size;
  if (num_shifts == 0) { return; }
  char* tmp = lkcpp::alloc<char>(buffer_size);
  lkcpp::memcpy(tmp + buffer_size - num_shifts, buffer, num_shifts);
  lkcpp::memcpy(tmp, buffer + num_shifts, buffer_size - num_shifts);
  lkcpp::memcpy(buffer, tmp, buffer_size);
  lkcpp::dealloc(tmp);
}

template<>
void memrshift(void* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts)
{
  memrshift<char>(static_cast<char*>(buffer), buffer_size, num_shifts);
}

template<>
void memrshift(char* buffer,
               lkcpp::size_t buffer_size,
               lkcpp::size_t num_shifts)
{
  if (buffer_size == 0) { return; }
  num_shifts %= buffer_size;
  if (num_shifts == 0) { return; }
  char* tmp = lkcpp::alloc<char>(buffer_size);
  lkcpp::memcpy(tmp + num_shifts, buffer, buffer_size - num_shifts);
  lkcpp::memcpy(tmp, buffer + buffer_size - num_shifts, num_shifts);
  lkcpp::memcpy(buffer, tmp, buffer_size);
  lkcpp::dealloc(tmp);
}
} // namespace lkcpp