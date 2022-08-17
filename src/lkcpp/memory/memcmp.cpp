#include "lkcpp/memory/memcmp.hpp"

namespace lkcpp {
template<>
int memcmp(void const* p1, void const* p2, lkcpp::size_t size)
{
  return lkcpp::memcmp(
    static_cast<char const*>(p1), static_cast<char const*>(p2), size);
}

template<>
int memcmp(char const* p1, char const* p2, lkcpp::size_t size)
{
  if (p1 == p2) { return 0; }

  for (lkcpp::size_t i = 0; i < size; i++) {
    if (p1[i] > p2[i]) {
      return 1;
    } else if (p1[i] < p2[i]) {
      return -1;
    }
  }
  return 0;
}
} // namespace lkcpp