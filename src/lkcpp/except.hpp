#pragma once

#include <stdexcept>
#include <string>

namespace lkcpp {
class out_of_bounds_exception : public std::exception {
public:
  out_of_bounds_exception(int number,
                          int start_bound,
                          int end_bound_inclusive) :
      m_what("Out of bounds exception: " + std::to_string(number) +
             " is not in the range [" + std::to_string(start_bound) + ", " +
             std::to_string(end_bound_inclusive) + "].")
  {}

  char const* what() { return m_what.c_str(); }

private:
  std::string const m_what;
};
} // namespace lkcpp