////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/except.hpp"
#include "lkcpp/memory.hpp"
#include "lkcpp/object.hpp"

#include <iostream>

namespace lkcpp {
/// Array wrapper class
/// Modeled after std::array
template<class T, lkcpp::size_t Size>
class array {
public:
  array() = default;
  virtual ~array() = default;

  /// Copies as much of the other array as will fit
  /// @param arr Array to copy elements from
  template<class Other_T, lkcpp::size_t Other_size>
  array(Other_T arr[Other_size]);
  /// Copies as much of the other array as will fit
  /// @param arr Array to copy elements from
  template<class Other_T, lkcpp::size_t Other_size>
  array(array<Other_T, Other_size> const& arr);

  /// @returns A reference to the element at the provided index
  T& at(lkcpp::size_t index);
  /// @returns A const reference to the element at the provided index
  T const& at(lkcpp::size_t index) const;
  /// @returns A reference to the element at the provided index
  T& operator[](lkcpp::size_t index) { return at(index); }
  /// @returns A const reference to the element at the provided index
  T const& operator[](lkcpp::size_t index) const { return at(index); }
  /// @returns A reference to the first element in the array
  T& front() { return at(0); }
  /// @returns A const reference to the first element in the array
  T const& front() const { return at(0); }
  /// @returns A reference to the last element in the array
  T& back() { return at(Size - 1); }
  /// @returns A const reference to the last element in the array
  T const& back() const { return at(Size - 1); }
  /// @returns A const pointer to the first element in the array
  T const* data() const { return m_data; }

  /// @returns The number of elements in the array
  lkcpp::size_t size() const { return Size; }

  /// Fills the array with the provided value
  void fill(T&& value);

  /// Outputs an array to a stream
  friend std::ostream& operator<<(std::ostream& os, array<T, Size> const& arr)
  {
    os << "{";
    for (lkcpp::size_t i = 0; i < Size; i++) {
      os << arr[i];
      if (i != Size - 1) { os << ", "; }
    }
    return (os << "}");
  }

private:
  T m_data[Size];
};

template<class T, lkcpp::size_t Size>
template<class Other_T, lkcpp::size_t Other_size>
array<T, Size>::array(Other_T arr[Other_size])
{
  // Use this approach rather than memcpy to call appropriate assignment
  // operators
  lkcpp::size_t min = (Other_size > Size) ? Size : Other_size;
  for (lkcpp::size_t i = 0; i < min; i++) { m_data[i] = arr[i]; }
}

template<class T, lkcpp::size_t Size>
template<class Other_T, lkcpp::size_t Other_size>
array<T, Size>::array(array<Other_T, Other_size> const& arr)
{
  // Use this approach rather than memcpy to call appropriate assignment
  // operators
  lkcpp::size_t min = (Other_size > Size) ? Size : Other_size;
  for (lkcpp::size_t i = 0; i < min; i++) { m_data[i] = arr[i]; }
}

template<class T, lkcpp::size_t Size>
T& array<T, Size>::at(lkcpp::size_t index)
{
  if (index >= Size) { throw out_of_bounds_exception(index, 0, Size - 1); }
  return m_data[index];
}

template<class T, lkcpp::size_t Size>
T const& array<T, Size>::at(lkcpp::size_t index) const
{
  if (index >= Size) { throw out_of_bounds_exception(index, 0, Size - 1); }
  return m_data[index];
}

template<class T, lkcpp::size_t Size>
void array<T, Size>::fill(T&& value)
{
  for (lkcpp::size_t i = 0; i < Size; i++) { m_data[i] = value; }
}
} // namespace lkcpp

template<class T_l, lkcpp::size_t Size_l, class T_r, lkcpp::size_t Size_r>
bool operator==(lkcpp::array<T_l, Size_l> const& lhs,
                lkcpp::array<T_r, Size_r> const& rhs) const
{
  if (lkcpp::is(lhs, rhs)) { return true; }
  if (Size != Other_size) { return false; }
  for (lkcpp::size_t i = 0; i < Size; i++) {
    if (lhs[i] != rhs[i]) { return false; }
  }
  return true;
}

template<class T_l, lkcpp::size_t Size_l, class T_r, lkcpp::size_t Size_r>
inline bool operator!=(lkcpp::array<T_l, Size_l> const& lhs,
                       lkcpp::array<T_r, Size_r> const& rhs) const
{
  return !(lhs == rhs);
}

template<class T_l, lkcpp::size_t Size_l, class T_r, lkcpp::size_t Size_r>
bool operator>(lkcpp::array<T_l, Size_l> const& lhs,
               lkcpp::array<T_r, Size_r> const& rhs) const
{
  if (lkcpp::is(lhs, rhs)) { return false; }
  lkcpp::size_t min = (Size_l > Size_r) ? Size_r : Size_l;
  for (lkcpp::size_t i = 0; i < min; i++) {
    if (lhs[i] > rhs[i]) { return true; }
  }
  return Size_l > Size_r;
}

template<class T_l, lkcpp::size_t Size_l, class T_r, lkcpp::size_t Size_r>
bool operator<(lkcpp::array<T_l, Size_l> const& lhs,
               lkcpp::array<T_r, Size_r> const& rhs) const
{
  if (lkcpp::is(lhs, rhs)) { return false; }
  lkcpp::size_t min = (Size_r > Size_l) ? Size_l : Size_r;
  for (lkcpp::size_t i = 0; i < min; i++) {
    if (lhs[i] < rhs[i]) { return true; }
  }
  return Size_l < Size_r;
}

template<class T_l, lkcpp::size_t Size_l, class T_r, lkcpp::size_t Size_r>
inline bool operator>=(lkcpp::array<T_l, Size_l> const& lhs,
                       lkcpp::array<T_r, Size_r> const& rhs) const
{
  return !(lhs < rhs);
}

template<class T_l, lkcpp::size_t Size_l, class T_r, lkcpp::size_t Size_r>
inline bool operator<=(lkcpp::array<T_l, Size_l> const& lhs,
                       lkcpp::array<T_r, Size_r> const& rhs) const
{
  return !(lhs > rhs);
}