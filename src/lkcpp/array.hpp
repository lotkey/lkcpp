////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/except.hpp"
#include "lkcpp/memory.hpp"

#include <iostream>

namespace lkcpp {
/// Array wrapper class
/// Modeled after std::array
template<class T, size_t Size>
class array {
public:
  array() = default;
  virtual ~array() = default;

  /// Copies as much of the other array as will fit
  /// @param arr Array to copy elements from
  template<class Other_T, size_t Other_size>
  array(Other_T arr[Other_size]);
  /// Copies as much of the other array as will fit
  /// @param arr Array to copy elements from
  template<class Other_T, size_t Other_size>
  array(array<Other_T, Other_size> const& arr);

  /// @returns True if the arrays contain equal elements and are the same size
  template<class Other_T, size_t Other_size>
  bool operator==(array<Other_T, Other_size> const& other) const;
  /// @returns False if the arrays contain equal elements and are the same size
  template<class Other_T, size_t Other_size>
  bool operator!=(array<Other_T, Other_size> const& other) const;
  /// @returns True if the first different element is greater than the
  /// corresponding element in the other array OR true if all corresponding
  /// elements are equal and the size is greater than the other array's size
  template<class Other_T, size_t Other_size>
  bool operator>(array<Other_T, Other_size> const& other) const;
  /// @returns True if the first different element is less than the
  /// corresponding element in the other array OR true if all corresponding
  /// elements are equal and the size is less than the other array's size
  template<class Other_T, size_t Other_size>
  bool operator<(array<Other_T, Other_size> const& other) const;
  /// @returns False if the first different element is less than the
  /// corresponding element in the other array OR true if all corresponding
  /// elements are equal and the size is greater than or equal to the other
  /// array's size
  template<class Other_T, size_t Other_size>
  bool operator>=(array<Other_T, Other_size> const& other) const;
  /// @returns False if the first different element is greater than the
  /// corresponding element in the other array OR true if all corresponding
  /// elements are equal and the size is less than or equal to the other array's
  /// size
  template<class Other_T, size_t Other_size>
  bool operator<=(array<Other_T, Other_size> const& other) const;

  /// @returns A reference to the element at the provided index
  T& at(size_t index);
  /// @returns A const reference to the element at the provided index
  T const& at(size_t index) const;
  /// @returns A reference to the element at the provided index
  T& operator[](size_t index) { return at(index); }
  /// @returns A const reference to the element at the provided index
  T const& operator[](size_t index) const { return at(index); }
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
  size_t size() const { return Size; }

  /// Fills the array with the provided value
  void fill(T&& value);
  /// Swaps the values in two arrays
  void swap(array<T, Size>& other);

  /// Outputs an array to a stream
  friend std::ostream& operator<<(std::ostream& os, array<T, Size> const& arr)
  {
    os << "{";
    for (size_t i = 0; i < Size; i++) {
      os << arr[i];
      if (i != Size - 1) { os << ", "; }
    }
    return (os << "}");
  }

private:
  T m_data[Size];
};

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
array<T, Size>::array(Other_T arr[Other_size])
{
  // Use this approach rather than memcpy to call appropriate assignment
  // operators
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) { m_data[i] = arr[i]; }
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
array<T, Size>::array(array<Other_T, Other_size> const& arr)
{
  // Use this approach rather than memcpy to call appropriate assignment
  // operators
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) { m_data[i] = arr[i]; }
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
bool array<T, Size>::operator==(array<Other_T, Other_size> const& other) const
{
  if (Size != Other_size) { return false; }
  for (size_t i = 0; i < Size; i++) {
    if (m_data[i] != other[i]) { return false; }
  }
  return true;
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
bool array<T, Size>::operator!=(array<Other_T, Other_size> const& other) const
{
  return !(*this == other);
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
bool array<T, Size>::operator>(array<Other_T, Other_size> const& other) const
{
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) {
    if (m_data[i] > other[i]) { return true; }
  }
  return Size > Other_size;
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
bool array<T, Size>::operator<(array<Other_T, Other_size> const& other) const
{
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) {
    if (m_data[i] < other[i]) { return true; }
  }
  return Size < Other_size;
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
bool array<T, Size>::operator>=(array<Other_T, Other_size> const& other) const
{
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) {
    if (m_data[i] < other[i]) { return false; }
  }
  return Size >= Other_size;
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
bool array<T, Size>::operator<=(array<Other_T, Other_size> const& other) const
{
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) {
    if (m_data[i] > other[i]) { return false; }
  }
  return Size <= Other_size;
}

template<class T, size_t Size>
T& array<T, Size>::at(size_t index)
{
  if (index >= Size) { throw out_of_bounds_exception(index, 0, Size - 1); }
  return m_data[index];
}

template<class T, size_t Size>
T const& array<T, Size>::at(size_t index) const
{
  if (index >= Size) { throw out_of_bounds_exception(index, 0, Size - 1); }
  return m_data[index];
}

template<class T, size_t Size>
void array<T, Size>::fill(T&& value)
{
  for (size_t i = 0; i < Size; i++) { m_data[i] = value; }
}

template<class T, size_t Size>
void array<T, Size>::swap(array<T, Size>& other)
{
  T* tmp = lkcpp::alloc<T>(Size);
  lkcpp::memcpy(tmp, m_data, Size);
  lkcpp::memcpy(m_data, other.m_data, Size);
  lkcpp::memcpy(other.m_data, tmp, Size);
  lkcpp::dealloc(tmp);
}
} // namespace lkcpp