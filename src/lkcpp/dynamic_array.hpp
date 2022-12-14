////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/except.hpp"
#include "lkcpp/memory.hpp"
#include "lkcpp/object.hpp"
#include "lkcpp/utility.hpp"

#include <type_traits>

namespace lkcpp {
/// Dynamic, resizable array that is stored on the heap
template<class T>
class dynamic_array {
public:
  dynamic_array() = default;
  dynamic_array(dynamic_array&& arr) = default;
  dynamic_array& operator=(dynamic_array&& arr) = default;
  virtual ~dynamic_array() = default;

  /// Allocates an array of the provided size
  /// @param size Number of elements to allocate
  dynamic_array(lkcpp::size_t size);
  /// Copies some data into a dynamic array
  /// @param data Source of data to copy from
  /// @param size Number of elements to copy from data
  dynamic_array(T const* data, lkcpp::size_t size);
  /// Performs a deep copy of a dynamic_array
  /// @param arr dynamic_array to deep copy
  dynamic_array(dynamic_array const& arr);
  /// Frees memory and performs a deep copy of a dynamic_array
  /// @param arr dynamic_array to deep copy
  dynamic_array& operator=(dynamic_array const& arr);

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
  T& back() { return at(size() - 1); }
  /// @returns A const reference to the last element in the array
  T const& back() const { return at(size() - 1); }
  /// @returns A const pointer to the first element in the array
  T const* data() const { return m_data.get(); }

  /// @returns The number of elements in the array
  lkcpp::size_t size() const { return m_data.size(); }
  /// Resizes the array to the provided size, deallocating any objects that get
  /// freed
  void resize(lkcpp::size_t size);

  /// Fills the array with the provided value
  void fill(T const& value);

  /// Outputs an array to a stream
  friend std::ostream& operator<<(std::ostream& os, dynamic_array<T> const& arr)
  {
    os << "{";
    for (lkcpp::size_t i = 0; i < arr.size(); i++) {
      os << arr[i];
      if (i != arr.size() - 1) { os << ", "; }
    }
    return (os << "}");
  }

private:
  lkcpp::unique_ptr<T> m_data;
};

template<class T>
dynamic_array<T>::dynamic_array(lkcpp::size_t size) :
    m_data(lkcpp::unique_ptr<T>::make_array(size))
{
  static_assert(std::is_default_constructible_v<T>);
}

template<class T>
dynamic_array<T>::dynamic_array(T const* data, lkcpp::size_t size)
{
  static_assert(std::is_default_constructible_v<T>);
  static_assert(std::is_assignable_v<T>);

  T* data_copy = lkcpp::alloc_objs<T>(size);
  for (lkcpp::size_t i = 0; i < size; i++) { data_copy[i] = data[i]; }
  m_data.reset(data_copy, size);
}

template<class T>
dynamic_array<T>::dynamic_array(dynamic_array<T> const& arr)
{
  static_assert(std::is_default_constructible_v<T>);
  static_assert(std::is_copy_assignable_v<T>);

  if (!arr.m_data) { return; }
  T* data = lkcpp::alloc_objs<T>(arr.size());
  for (lkcpp::size_t i = 0; i < arr.size(); i++) { data[i] = arr.m_data[i]; }
  m_data.reset(data, arr.size());
}

template<class T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T> const& arr)
{
  static_assert(std::is_default_constructible_v<T>);
  static_assert(std::is_copy_assignable_v<T>);

  if (!arr.m_data) { return *this; }
  T* data = lkcpp::alloc_objs<T>(arr.size());
  for (lkcpp::size_t i = 0; i < arr.size(); i++) { data[i] = arr.m_data[i]; }
  m_data.reset(data, arr.size());
}

template<class T>
void dynamic_array<T>::resize(lkcpp::size_t size)
{
  T* data = m_data.release();
  data = lkcpp::realloc_objs(data, m_data.size(), size);
  m_data.reset(data, size);
}

template<class T>
T& dynamic_array<T>::at(lkcpp::size_t index)
{
  if (index >= size()) { throw out_of_bounds_exception(index, 0, size() - 1); }
  return m_data[index];
}

template<class T>
T const& dynamic_array<T>::at(lkcpp::size_t index) const
{
  if (index >= size()) { throw out_of_bounds_exception(index, 0, size() - 1); }
  return m_data[index];
}

template<class T>
void dynamic_array<T>::fill(T const& value)
{
  for (lkcpp::size_t i = 0; i < size(); i++) { m_data[i] = value; }
}
} // namespace lkcpp

template<class T>
bool operator==(lkcpp::dynamic_array<T> const& lhs,
                lkcpp::dynamic_array<T> const& rhs) const
{
  if (lkcpp::is(lhs, rhs)) { return true; }
  if (lhs.size() != rhs.size()) { return false; }
  return lkcpp::memcmp(lhs.data(), rhs.data(), lhs.size()) == 0;
}

template<class T>
inline bool operator!=(lkcpp::dynamic_array<T> const& lhs,
                       lkcpp::dynamic_array<T> const& rhs) const
{
  return !(lhs == rhs);
}

template<class T>
bool operator>(lkcpp::dynamic_array<T> const& lhs,
               lkcpp::dynamic_array<T> const& rhs) const
{
  if (lkcpp::is(lhs, rhs)) { return false; }
  lkcpp::size_t min = (lhs.size() > rhs.size()) ? rhs.size() : lhs.size();
  for (lkcpp::size_t i = 0; i < min; i++) {
    if (lhs[i] > rhs[i]) { return true; }
  }
  return lhs.size() > rhs.size();
}

template<class T>
bool operator<(lkcpp::dynamic_array<T> const& lhs,
               lkcpp::dynamic_array<T> const& rhs) const
{
  if (lkcpp::is(lhs, rhs)) { return false; }
  lkcpp::size_t min = (lhs.size() > rhs.size()) ? rhs.size() : lhs.size();
  for (lkcpp::size_t i = 0; i < min; i++) {
    if (lhs[i] < rhs[i]) { return true; }
  }
  return lhs.size() < rhs.size();
}

template<class T>
inline bool operator>=(lkcpp::dynamic_array<T> const& lhs,
                       lkcpp::dynamic_array<T> const& rhs) const
{
  return !(lhs < rhs);
}

template<class T>
inline bool operator<=(lkcpp::dynamic_array<T> const& lhs,
                       lkcpp::dynamic_array<T> const& rhs) const
{
  return !(lhs > rhs);
}