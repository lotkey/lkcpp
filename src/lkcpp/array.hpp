#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/except.hpp"

#include <iostream>

namespace lkcpp {
template<class T, size_t Size>
class array {
public:
  array() = default;
  template<class Other_T, size_t Other_size>
  array(Other_T arr[Other_size]);
  template<class Other_T, size_t Other_size>
  array(array<Other_T, Other_size> const& arr);
  array<T, Size>& operator=(array<T, Size> const& arr);
  virtual ~array() = default;

  template<class Other_T, size_t Other_size>
  bool operator==(array<Other_T, Other_size> const& other) const;
  template<class Other_T, size_t Other_size>
  bool operator!=(array<Other_T, Other_size> const& other) const;
  template<class Other_T, size_t Other_size>
  bool operator>(array<Other_T, Other_size> const& other) const;
  template<class Other_T, size_t Other_size>
  bool operator<(array<Other_T, Other_size> const& other) const;
  template<class Other_T, size_t Other_size>
  bool operator>=(array<Other_T, Other_size> const& other) const;
  template<class Other_T, size_t Other_size>
  bool operator<=(array<Other_T, Other_size> const& other) const;

  T& at(size_t index);
  T const& at(size_t index) const;
  T& operator[](size_t index) { return at(index); }
  T const& operator[](size_t index) const { return at(index); }
  T& front() { return at(0); }
  T const& front() const { return at(0); }
  T& back() { return at(Size - 1); }
  T const& back() const { return at(Size - 1); }
  T const* data() const { return m_data; }

  size_t size() const { return Size; }

  void fill(T const& value);

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
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) { m_data[i] = arr[i]; }
}

template<class T, size_t Size>
template<class Other_T, size_t Other_size>
array<T, Size>::array(array<Other_T, Other_size> const& arr)
{
  size_t min = (Other_size > Size) ? Size : Other_size;
  for (size_t i = 0; i < min; i++) { m_data[i] = arr[i]; }
}

template<class T, size_t Size>
array<T, Size>& array<T, Size>::operator=(array<T, Size> const& arr)
{
  for (size_t i = 0; i < Size; i++) { m_data[i] = arr[i]; }
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
void array<T, Size>::fill(T const& value)
{
  for (size_t i = 0; i < Size; i++) { m_data[i] = value; }
}
} // namespace lkcpp