#include "lkcpp/memory/memcpy.hpp"

namespace lkcpp {
template<>
void memcpy(void* dest, void const* source, lkcpp::size_t num_bytes)
{
  lkcpp::memcpy(
    static_cast<char*>(dest), static_cast<char const*>(source), num_bytes);
}

template<>
void memcpy(char* dest, char const* source, lkcpp::size_t num_bytes)
{
  //   Case 1:
  //     Regions are the same.
  //     |__source__|
  //     |___dest___|
  if (dest == source) {
    return;
  }
  //   Case 2:
  //     Regions overlap, and the destination is first.
  //        |__source__|
  //     |___dest___|
  else if (dest < source && dest + num_bytes > source) {
    // Copy from left to right
    // This will overwrite the source
    for (lkcpp::size_t i = 0; i < num_bytes; i++) { dest[i] = source[i]; }
  }
  //   Case 3:
  //     Regions overlap, and the source is first.
  //     |__source__|
  //        |___dest___|
  else if (source < dest && source + num_bytes > dest) {
    // Copy from right to left
    // This will overwrite the source
    for (lkcpp::size_t i = num_bytes; i > 0; i--) {
      dest[i - 1] = source[i - 1];
    }
  }
  //   Case 4:
  //     Regions are not overlapping at all.
  //     |__source__|
  //                      |___dest___|
  else {
    // Copy from left to right (order is arbitrary)
    for (lkcpp::size_t i = 0; i < num_bytes; i++) { dest[i] = source[i]; }
  }
}
} // namespace lkcpp