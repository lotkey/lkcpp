#include "lkcpp/memory/alloc.hpp"

namespace lkcpp {
template<>
void* alloc(lkcpp::size_t size)
{
  lkcpp::size_t* p =
    static_cast<lkcpp::size_t*>(std::malloc(sizeof(lkcpp::size_t) + size));
  if (p == nullptr) {
    throw failed_allocation_exception(sizeof(lkcpp::size_t) + size);
  }
  *p = size;
  return static_cast<void*>(p + 1);
}

template<>
void* realloc(void* t, lkcpp::size_t size)
{
  if (t == nullptr) { return lkcpp::alloc<void>(size); }
  lkcpp::size_t* p = static_cast<lkcpp::size_t*>(t) - 1;
  lkcpp::size_t* new_data =
    static_cast<lkcpp::size_t*>(std::realloc(p, sizeof(lkcpp::size_t) + size));
  if (new_data == nullptr) {
    throw failed_allocation_exception(sizeof(lkcpp::size_t) + size);
  }
  *new_data = size;
  return static_cast<void*>(new_data + 1);
}
} // namespace lkcpp