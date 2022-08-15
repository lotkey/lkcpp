#pragma once

#include "lkcpp/algorithm.hpp"
#include "lkcpp/except.hpp"
#include "lkcpp/memory.hpp"
#include "lkcpp/utility.hpp"

#include <type_traits>

namespace lkcpp {
template<class T>
class dynamic_array {
public:
  dynamic_array() = default;
  dynamic_array(size_t size);
  dynamic_array(T const* data, size_t size);
  dynamic_array(dynamic_array const& arr);
  dynamic_array(dynamic_array&& arr) = default;
  dynamic_array& operator=(dynamic_array const& arr);
  dynamic_array& operator=(dynamic_array&& arr) = default;
  virtual ~dynamic_array() = default;

  bool operator==(dynamic_array const& other) const;
  bool operator!=(dynamic_array const& other) const;
  bool operator>(dynamic_array const& other) const;
  bool operator<(dynamic_array const& other) const;
  bool operator>=(dynamic_array const& other) const;
  bool operator<=(dynamic_array const& other) const;

  T& at(size_t index);
  T const& at(size_t index) const;
  T& operator[](size_t index) { return at(index); }
  T const& operator[](size_t index) const { return at(index); }
  T& front() { return at(0); }
  T const& front() const { return at(0); }
  T& back() { return at(size() - 1); }
  T const& back() const { return at(size() - 1); }
  T const* data() const { return m_data.get(); }

  size_t size() const { return m_data.size(); }
  void resize(size_t size);

  void fill(T const& value);
  void swap(dynamic_array<T>& arr);

  friend std::ostream& operator<<(std::ostream& os, dynamic_array<T> const& arr)
  {
    os << "{";
    for (size_t i = 0; i < arr.size(); i++) {
      os << arr[i];
      if (i != arr.size() - 1) { os << ", "; }
    }
    return (os << "}");
  }

private:
  unique_ptr<T> m_data;
};

template<class T>
dynamic_array<T>::dynamic_array(size_t size) :
    m_data(make_unique_array<T>(size))
{
  static_assert(std::is_default_constructible_v<T>);
}

template<class T>
dynamic_array<T>::dynamic_array(T const* data, size_t size)
{
  static_assert(std::is_default_constructible_v<T>);
  static_assert(std::is_assignable_v<T>);

  T* data_copy = lkcpp::alloc_objs<T>(size);
  for (size_t i = 0; i < size; i++) { data_copy[i] = data[i]; }
  m_data.reset(data_copy, size);
}

template<class T>
dynamic_array<T>::dynamic_array(dynamic_array<T> const& arr)
{
  static_assert(std::is_default_constructible_v<T>);
  static_assert(std::is_copy_assignable_v<T>);

  if (!arr.m_data) { return; }
  T* data = lkcpp::alloc_objs<T>(arr.size());
  for (size_t i = 0; i < arr.size(); i++) { data[i] = arr.m_data[i]; }
  m_data.reset(data, arr.size());
}

template<class T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T> const& arr)
{
  static_assert(std::is_default_constructible_v<T>);
  static_assert(std::is_copy_assignable_v<T>);

  if (!arr.m_data) { return *this; }
  T* data = lkcpp::alloc_objs<T>(arr.size());
  for (size_t i = 0; i < arr.size(); i++) { data[i] = arr.m_data[i]; }
  m_data.reset(data, arr.size());
}

template<class T>
bool dynamic_array<T>::operator==(dynamic_array<T> const& other) const
{
  if (size() != other.size()) { return false; }
  return lkcpp::equal(
    m_data.get(), m_data.get() + m_data.size(), other.m_data.get());
}

template<class T>
bool dynamic_array<T>::operator!=(dynamic_array<T> const& other) const
{
  return !(*this == other);
}

template<class T>
bool dynamic_array<T>::operator>(dynamic_array<T> const& other) const
{
  size_t min = (other.size() > size()) ? size() : other.size();
  for (size_t i = 0; i < min; i++) {
    if (at(i) > other[i]) { return true; }
  }
  return size() > other.size();
}

template<class T>
bool dynamic_array<T>::operator<(dynamic_array<T> const& other) const
{
  size_t min = (other.size() > size()) ? size() : other.size();
  for (size_t i = 0; i < min; i++) {
    if (at(i) < other[i]) { return true; }
  }
  return size() < other.size();
}

template<class T>
bool dynamic_array<T>::operator>=(dynamic_array<T> const& other) const
{
  size_t min = (other.size() > size()) ? size() : other.size();
  for (size_t i = 0; i < min; i++) {
    if (at(i) < other[i]) { return false; }
  }
  return size() >= other.size();
}

template<class T>
bool dynamic_array<T>::operator<=(dynamic_array<T> const& other) const
{
  size_t min = (other.size() > size()) ? size() : other.size();
  for (size_t i = 0; i < min; i++) {
    if (at(i) > other[i]) { return false; }
  }
  return size() <= other.size();
}

template<class T>
void dynamic_array<T>::resize(size_t size)
{
  T* data = lkcpp::alloc<T>(size);
  lkcpp::memcpy(
    data, m_data.get(), (size > m_data.size()) ? m_data.size() : size);
  lkcpp::dealloc(m_data.release());
  m_data.reset(data, size);
}

template<class T>
T& dynamic_array<T>::at(size_t index)
{
  if (index >= size()) { throw out_of_bounds_exception(index, 0, size() - 1); }
  return m_data[index];
}

template<class T>
T const& dynamic_array<T>::at(size_t index) const
{
  if (index >= size()) { throw out_of_bounds_exception(index, 0, size() - 1); }
  return m_data[index];
}

template<class T>
void dynamic_array<T>::fill(T const& value)
{
  for (size_t i = 0; i < size(); i++) { m_data[i] = value; }
}

template<class T>
void dynamic_array<T>::swap(dynamic_array<T>& arr)
{
  lkcpp::swap(arr.m_data, m_data);
}
} // namespace lkcpp