////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"

#include <stdexcept>
#include <string>

namespace lkcpp {
/// Exception for a failed heap allocation
class failed_allocation_exception : public std::exception {
public:
  /// Construct exception
  /// @param allocation_size The size (in bytes) of the attempted allocation
  failed_allocation_exception(lkcpp::size_t allocation_size);
  /// @returns A description of the exception
  virtual char const* what() const noexcept override;

private:
  std::string m_what;
};
} // namespace lkcpp