#include "lkcpp/memory/alloc.hpp"

namespace lkcpp {
template<>
void* alloc(lkcpp::size_t size)
{
  void* p = std::malloc(size);
  if (p == nullptr) { throw failed_allocation_exception(size); }
  return p;
}

template<>
void* realloc(void* t, lkcpp::size_t size)
{
  if (t == nullptr) { return lkcpp::alloc<void>(size); }
  void* new_data = std::realloc(t, size);
  if (new_data == nullptr) { throw failed_allocation_exception(size); }
  return new_data;
}
} // namespace lkcpp