#include "lkcpp/except/failed_allocation.hpp"

namespace lkcpp {
failed_allocation_exception::failed_allocation_exception(
  lkcpp::size_t allocation_size) :
    m_what("Failed allocation of " + std::to_string(allocation_size) +
           " bytes.")
{}

char const* failed_allocation_exception::what() const noexcept
{
  return m_what.c_str();
}
} // namespace lkcpp