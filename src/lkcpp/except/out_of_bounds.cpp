#include "lkcpp/except/out_of_bounds.hpp"

namespace lkcpp {
char const* out_of_bounds_exception::what() const noexcept
{
  return m_what.c_str();
}
} // namespace lkcpp