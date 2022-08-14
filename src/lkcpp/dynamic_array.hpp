#pragma once

#include "lkcpp/algorithm.hpp"
#include "lkcpp/except.hpp"
#include "lkcpp/memory.hpp"
#include "lkcpp/utility.hpp"

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
{}

template<class T>
dynamic_array<T>::dynamic_array(T const* data, size_t size)
{
  auto ptr = make_unique_array<T>(size);
  T* data_copy = ptr.release();
  lkcpp::memcpy(data_copy, data, size);
  m_data.reset(data_copy, size);
}

template<class T>
dynamic_array<T>::dynamic_array(dynamic_array<T> const& arr)
{
  if (!arr.m_data) { return; }
  auto ptr = make_unique_array<T>(arr.size());
  T* data = ptr.release();
  lkcpp::memcpy(data, arr.data(), sizeof(T) * arr.size());
  m_data.reset(data, arr.size());
}

template<class T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T> const& arr)
{
  T* data = make_unique_array<T>(arr.size());
  lkcpp::memcpy(data, arr.data(), sizeof(T) * arr.size());
  m_data.reset(data, arr.size());
}

template<class T>
bool dynamic_array<T>::operator==(dynamic_array<T> const& other) const
{
  if (size() != other.size()) { return false; }
  if (size() == 0) { return true; }
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
  auto p = make_unique_array<T>(size);
  T* data = p.release();
  lkcpp::memcpy(
    data, m_data.get(), (size > m_data.size()) ? m_data.size() : size);
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