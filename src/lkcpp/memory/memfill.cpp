#include "lkcpp/memory/memfill.hpp"

namespace lkcpp {
void memfill(void* dest, char value, lkcpp::size_t count)
{
  lkcpp::memfill(static_cast<char*>(dest), value, count);
}
} // namespace lkcpp