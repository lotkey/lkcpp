////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/except.hpp"
#include "lkcpp/memory/alloc.hpp"
#include "lkcpp/memory/memshift.hpp"
#include "lkcpp/object.hpp"
#include "lkcpp/utility.hpp"

namespace lkcpp {
/// Contiguous container of memory
/// Modeled after std::vector
template<class T>
class vector {
public:
  /// Default constructor, empty vector
  vector();
  /// Creates and constructs a vector of objects
  /// @param initial_size Number of objects to construct
  /// @param args Constructor arguments
  template<class... Args>
  vector(lkcpp::size_t initial_size, Args&&... args);
  /// Creates and constructs a vector of objects by copying
  /// @param data Pointer to data to copy
  /// @param size Number of elements to copy into the vector
  vector(T const* data, lkcpp::size_t size);
  /// Copies objects from another vector
  vector(vector<T> const& other);
  /// Moves objects from another vector
  vector(vector<T>&& other);
  /// Clear vector and copy objects from another vector
  vector<T>& operator=(vector<T> const& other);
  /// Clear vector and move objects from another vector
  vector<T>& operator=(vector<T>&& other);
  /// Clear vector
  virtual ~vector();

  T& at(lkcpp::size_t index);
  T const& at(lkcpp::size_t index) const;
  T& operator[](lkcpp::size_t index) { return at(index); }
  T const& operator[](lkcpp::size_t index) const { return at(index); }
  T& front() { return at(0); }
  T const& front() const { return at(0); }
  T& back() { return at(m_size - 1); }
  T const& back() const { return at(m_size - 1); }
  T const* data() const { return m_data; }

  bool empty() const { return m_size == 0; }
  lkcpp::size_t size() const { return m_size; }

  void clear();
  template<class... Args>
  void insert(lkcpp::size_t index, Args&&... args);
  void erase(lkcpp::size_t index);
  void erase(lkcpp::size_t start, lkcpp::size_t last);
  template<class... Args>
  void push_back(Args&&... args);
  void pop_back();

  bool operator==(vector<T> const& v) const;
  bool operator!=(vector<T> const& v) const;
  bool operator>(vector<T> const& v) const;
  bool operator<(vector<T> const& v) const;
  bool operator>=(vector<T> const& v) const;
  bool operator<=(vector<T> const& v) const;

  friend std::ostream& operator<<(std::ostream& os, vector<T> const& v)
  {
    os << "{";
    for (lkcpp::size_t i = 0; i < v.size() - 1; i++) { os << v[i] << ", "; }
    if (!empty()) { os << back(); }
    return (os << "}");
  }

private:
  static constexpr lkcpp::size_t s_first_size = 10;

  T* m_data;
  lkcpp::size_t m_size = 0;
  lkcpp::size_t m_capacity = 0;

  void alloc_more_if_needed(lkcpp::size_t room_needed = 1);
  void shrink_if_needed();
  void shift_right(lkcpp::size_t index_start, lkcpp::size_t num_shifts);
  void shift_left(lkcpp::size_t index_start, lkcpp::size_t num_shifts);
};

template<class T>
vector<T>::vector() :
    m_data(lkcpp::alloc<T>(s_first_size)), m_capacity(s_first_size)
{}

template<class T>
template<class... Args>
vector<T>::vector(lkcpp::size_t initial_size, Args&&... args) :
    m_data(lkcpp::alloc<T>(initial_size * 2)),
    m_capacity(initial_size * 2),
    m_size(initial_size)
{
  for (lkcpp::size_t i = 0; i < initial_size; i++) {
    lkcpp::construct(m_data + i, args...);
  }
}

template<class T>
vector<T>::vector(T const* data, lkcpp::size_t initial_size) :
    m_data(lkcpp::alloc<T>(initial_size * 2)),
    m_capacity(initial_size * 2),
    m_size(initial_size)
{
  for (lkcpp::size_t i = 0; i < initial_size; i++) {
    lkcpp::construct(m_data + i, data[i]);
  }
}

template<class T>
vector<T>::vector(vector<T> const& other) :
    m_data(lkcpp::alloc<T>(other.m_capacity)),
    m_capacity(other.m_capacity),
    m_size(other.m_size)
{
  for (lkcpp::size_t i = 0; i < m_size; i++) {
    lkcpp::construct(m_data + i, other[i]);
  }
}

template<class T>
vector<T>::vector(vector<T>&& other) :
    m_data(other.m_data), m_capacity(other.m_capacity), m_size(other.m_size)
{
  other.m_data = nullptr;
  other.m_capacity = 0;
  other.m_size = 0;
}

template<class T>
vector<T>& vector<T>::operator=(vector<T> const& other)
{
  clear();
  m_data = lkcpp::alloc<T>(other.m_capacity);
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  for (lkcpp::size_t i = 0; i < m_size; i++) {
    lkcpp::construct(m_data + i, other[i]);
  }
}

template<class T>
vector<T>& vector<T>::operator=(vector<T>&& other)
{
  clear();
  m_data = other.m_data;
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  other.m_data = nullptr;
  other.m_capacity = 0;
  other.m_size = 0;
}

template<class T>
vector<T>::~vector()
{
  clear();
}

template<class T>
T& vector<T>::at(lkcpp::size_t index)
{
  if (index >= m_size) {
    throw lkcpp::out_of_bounds_exception(index, 0, m_size - 1);
  }
  return m_data[index];
}

template<class T>
T const& vector<T>::at(lkcpp::size_t index) const
{
  if (index >= m_size) {
    throw lkcpp::out_of_bounds_exception(index, 0, m_size - 1);
  }
  return m_data[index];
}

template<class T>
void vector<T>::clear()
{
  for (lkcpp::size_t i = 0; i < m_size; i++) { lkcpp::destruct(m_data + i); }
  lkcpp::dealloc(m_data);
  m_data = nullptr;
  m_size = 0;
  m_capacity = s_first_size;
}

template<class T>
template<class... Args>
void vector<T>::insert(lkcpp::size_t index, Args&&... args)
{
  shift_right(index, 1);
  construct(m_data + index, args...);
  m_size++;
}

template<class T>
void vector<T>::erase(lkcpp::size_t index)
{
  shift_left(index, 1);
  m_size--;
  shrink_if_needed();
}

template<class T>
void vector<T>::erase(lkcpp::size_t start, lkcpp::size_t last)
{
  shift_left(start, last - start);
  m_size -= last - start;
  shrink_if_needed();
}

template<class T>
template<class... Args>
void vector<T>::push_back(Args&&... args)
{
  alloc_more_if_needed();
  lkcpp::construct(m_data + m_size, args...);
  m_size++;
}

template<class T>
void vector<T>::pop_back()
{
  if (m_size != 0) {
    lkcpp::destruct(m_data + m_size - 1);
    m_size--;
    shrink_if_needed();
  }
}

template<class T>
void vector<T>::alloc_more_if_needed(lkcpp::size_t room_needed)
{
  if (m_capacity - m_size > room_needed) { return; }

  if (m_capacity == 0) {
    m_data = lkcpp::realloc(m_data, s_first_size + (room_needed * 2));
  } else {
    if (m_capacity * 2 > room_needed) {
      m_data = lkcpp::realloc(m_data, m_capacity * 2);
    } else {
      m_data = lkcpp::realloc(m_data, m_capacity + (2 * room_needed));
    }
  }
}

template<class T>
void vector<T>::shrink_if_needed()
{
  if (m_size * 4 < m_capacity) { m_data = lkcpp::realloc(m_data, m_size * 2); }
}

template<class T>
void vector<T>::shift_right(lkcpp::size_t index_start, lkcpp::size_t num_shifts)
{
  alloc_more_if_needed(num_shifts);
  lkcpp::memrshift(m_data + index_start, m_capacity - index_start, num_shifts);
}

template<class T>
void vector<T>::shift_left(lkcpp::size_t index_start, lkcpp::size_t num_shifts)
{
  for (lkcpp::size_t i = 0; i < num_shifts; i++) {
    lkcpp::destruct(m_data + index_start + i);
  }
  lkcpp::memlshift(m_data + index_start, m_capacity - index_start, num_shifts);
}
} // namespace lkcpp