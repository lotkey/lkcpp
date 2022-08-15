#pragma once

#include "lkcpp/except.hpp"
#include "lkcpp/object.hpp"
#include "lkcpp/pod.hpp"
#include "lkcpp/pod_view.hpp"
#include "lkcpp/utility.hpp"

namespace lkcpp {
template<class T>
class vector {
public:
  vector() = default;
  vector(vector<T> const&) = default;
  vector(vector<T>&&) = default;
  vector<T>& operator=(vector<T> const&) = default;
  vector<T>& operator=(vector<T>&&) = default;
  virtual ~vector() = default;

  vector(size_t initial_size) : m_data(initial_size) {}
  vector(T const* data, size_t size);

  T& at(size_t index);
  T const& at(size_t index) const;
  T& operator[](size_t index) { return at(index); }
  T const& operator[](size_t index) const { return at(index); }
  T& front() { return at(0); }
  T const& front() const { return at(0); }
  T& back() { return at(m_size - 1); }
  T const& back() const { return at(m_size - 1); }
  T const* data() const { return m_data.array<T>(); }

  bool empty() const { return m_size == 0; }
  size_t size() const { return m_size; }

  void clear();
  template<class... Args>
  void insert(size_t index, Args&&... args);
  void erase(size_t index);
  void erase(size_t start, size_t last);
  template<class... Args>
  void push_back(Args&&... args);
  void pop_back();
  void swap(vector<T>& v);

  bool operator==(vector<T> const& v) const;
  bool operator!=(vector<T> const& v) const;
  bool operator>(vector<T> const& v) const;
  bool operator<(vector<T> const& v) const;
  bool operator>=(vector<T> const& v) const;
  bool operator<=(vector<T> const& v) const;

  friend std::ostream& operator<<(std::ostream& os, vector<T> const& v)
  {
    os << "{";
    for (size_t i = 0; i < v.size(); i++) {
      os << v[i];
      if (i != v.size() - 1) { os << ", "; }
    }
    return (os << "}");
  }

private:
  static constexpr size_t s_first_size = 10;

  pod m_data;
  size_t m_size = 0;

  void alloc_more_if_needed(size_t room_needed = 1);
  void shrink_if_needed();
  void shift_right(size_t index_start, size_t num_shifts);
  void shift_left(size_t index_start, size_t num_shifts);
};

template<class T>
vector<T>::vector(T const* data, size_t initial_size) :
    m_data(data, initial_size * sizeof(T) * 2)
{
  for (size_t i = 0; i < initial_size; i++) {
    construct(m_data.array<T>() + i);
  }
  m_size = initial_size;
}

template<class T>
T& vector<T>::at(size_t index)
{
  if (index >= m_size) { throw out_of_bounds_exception(index, 0, m_size - 1); }
  return m_data.array<T>()[index];
}

template<class T>
T const& vector<T>::at(size_t index) const
{
  if (index >= m_size) { throw out_of_bounds_exception(index, 0, m_size - 1); }
  return m_data.array<T>()[index];
}

template<class T>
void vector<T>::clear()
{
  for (size_t i = 0; i < m_size; i++) { destruct(m_data.array<T>() + i); }
  m_data.clear();
  m_size = 0;
}

template<class T>
template<class... Args>
void vector<T>::insert(size_t index, Args&&... args)
{
  shift_right(index, 1);
  construct(m_data.array<T>() + index, args...);
  m_size++;
}

template<class T>
void vector<T>::erase(size_t index)
{
  shift_left(index, 1);
  m_size--;
  shrink_if_needed();
}

template<class T>
void vector<T>::erase(size_t start, size_t last)
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
  construct(m_data.array<T>() + m_size, args...);
  m_size++;
}

template<class T>
void vector<T>::pop_back()
{
  if (m_size != 0) {
    destruct(m_data.array<T>() + m_size - 1);
    m_size--;
  }
  shrink_if_needed();
}

template<class T>
void vector<T>::swap(vector<T>& v)
{
  lkcpp::swap(m_data, v.m_data);
  lkcpp::swap(m_size, v.m_size);
}

template<class T>
void vector<T>::alloc_more_if_needed(size_t room_needed)
{
  if (m_data.size_in<T>() - m_size > room_needed) { return; }

  if (m_data.size_in<T>() == 0) {
    m_data.resize(sizeof(T) * (s_first_size + (room_needed * 2)));
  } else {
    if (m_data.size_in<T>() * 2 > room_needed) {
      m_data.resize(m_data.size() * 2);
    } else {
      m_data.resize(m_data.size() + (2 * room_needed));
    }
  }
}

template<class T>
void vector<T>::shrink_if_needed()
{
  if (m_size * 4 < m_data.size()) { m_data.resize(m_size * sizeof(T) * 2); }
}

template<class T>
void vector<T>::shift_right(size_t index_start, size_t num_shifts)
{
  alloc_more_if_needed();
  pod_view pv(m_data, index_start * sizeof(T));
  pv >> num_shifts;
}

template<class T>
void vector<T>::shift_left(size_t index_start, size_t num_shifts)
{
  for (size_t i = 0; i < num_shifts; i++) {
    destruct(m_data.array<T>() + index_start + i);
  }
  pod_view pv(m_data, index_start * sizeof(T));
  pv << num_shifts;
}
} // namespace lkcpp