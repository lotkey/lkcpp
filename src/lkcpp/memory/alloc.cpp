#include "lkcpp/memory/alloc.hpp"

namespace lkcpp {
template<>
void* alloc(size_t size)
{
  size_t* p = static_cast<size_t*>(std::malloc(sizeof(size_t) + size));
  *p = size;
  return static_cast<void*>(p + 1);
}

template<>
void* realloc(void* t, size_t size)
{
  size_t* p = static_cast<size_t*>(t) - 1;
  size_t* new_data =
    static_cast<size_t*>(std::realloc(p, sizeof(size_t) + size));
  return static_cast<void*>(new_data + 1);
}
} // namespace lkcpp