#pragma once

#include "lkcpp/def.hpp"

#include <stdexcept>
#include <string>

namespace lkcpp {
class failed_allocation_exception : public std::exception {
public:
  failed_allocation_exception(size_t allocation_size);
  virtual char const* what() const noexcept override;

private:
  std::string m_what;
};
} // namespace lkcpp