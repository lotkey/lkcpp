////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <stdexcept>
#include <string>

namespace lkcpp {
/// Exception for attempting to do something out of bounds
class out_of_bounds_exception : public std::exception {
public:
  /// Construct exception
  /// @param out_of_bounds Thing that was out of bounds
  /// @param start_bound First in-bound thing
  /// @param end_bound_inclusive Last in-bound thing
  template<class T1, class T2, class T3>
  out_of_bounds_exception(T1 const& out_of_bounds,
                          T2 const& start_bound,
                          T3 const& end_bound_inclusive);
  /// @returns A description of the exception
  virtual char const* what() const noexcept override;

private:
  std::string m_what;
};

template<class T1, class T2, class T3>
out_of_bounds_exception::out_of_bounds_exception(
  T1 const& number,
  T2 const& start_bound,
  T3 const& end_bound_inclusive) :
    m_what("Out of bounds exception: " + std::to_string(number) +
           " is not in the range [" + std::to_string(start_bound) + ", " +
           std::to_string(end_bound_inclusive) + "].")
{}
} // namespace lkcpp