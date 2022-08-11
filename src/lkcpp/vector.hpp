#pragma once

#include "lkcpp/dynamic_array.hpp"

namespace lkcpp {
template<class T>
class vector {
public:
  vector() = default;
  vector(size_t initial_size) : m_data(initial_size) {}
  vector(T const* data, size_t size);
  vector(vector<T> const&) = default;
  vector(vector<T>&&) = default;
  vector<T>& operator=(vector<T> const&) = default;
  vector<T>& operator=(vector<T>&&) = default;
  virtual ~vector() = default;

  T& at(size_t index);
  T const& at(size_t index) const;
  T& operator[](size_t index) { return at(index); }
  T const& operator[](size_t index) const { return at(index); }
  T& front() { return at(0); }
  T const& front() const { return at(0); }
  T& back() { return at(m_size - 1); }
  T const& back() const { return at(m_size - 1); }
  T const* data() const { return m_data.data(); }

  bool empty() const { return m_size == 0; }
  size_t size() const { return m_size; }

  void clear() const;
  void insert(size_t index, T const& t);
  void emplace(size_t index, T&& t);
  void erase(size_t index);
  void erase(size_t start, size_t last);
  void push_back(T const& t);
  void emplace_back(T&& t);
  void pop_back();
  void swap(vector<T>& v);

  bool operator==(vector<T> const& v) const;
  bool operator!=(vector<T> const& v) const;
  bool operator>(vector<T> const& v) const;
  bool operator<(vector<T> const& v) const;
  bool operator>=(vector<T> const& v) const;
  bool operator<=(vector<T> const& v) const;

private:
  static constexpr size_t s_first_size = 10;

  dynamic_array<T> m_data;
  size_t m_size = 0;

  void alloc_more_if_needed(size_t room_needed = 1);
  void shrink_if_needed();
};

template<class T>
vector<T>::vector(T const* data, size_t initial_size) :
    m_data(data, initial_size)
{
  m_data.resize(initial_size * 2);
  m_size = initial_size;
}

template<class T>
T& vector<T>::at(size_t index)
{
  if (index >= m_size) { throw out_of_bounds_exception(index, 0, m_size - 1); }
  return m_data.at(index);
}

template<class T>
T const& vector<T>::at(size_t index) const
{
  if (index >= m_size) { throw out_of_bounds_exception(index, 0, m_size - 1); }
  return m_data.at(index);
}

template<class T>
void vector<T>::clear() const
{
  m_data.resize(0);
  m_size = 0;
}

template<class T>
void vector<T>::insert(size_t index, T const& t)
{
  alloc_more_if_needed();
  for (size_t i = m_size; i > index; i++) { m_data[i] = m_data[i - 1]; }
  m_data[index] = t;
  m_size++;
}

template<class T>
void vector<T>::emplace(size_t index, T&& t)
{
  alloc_more_if_needed();
  for (size_t i = m_size; i > index; i++) { m_data[i] = m_data[i - 1]; }
  m_data[index] = t;
  m_size++;
}

template<class T>
void vector<T>::erase(size_t index)
{
  for (size_t i = index; i < m_size - 1; i++) { m_data[i] = m_data[i + 1]; }
  m_size--;
  shrink_if_needed();
}

template<class T>
void vector<T>::erase(size_t start, size_t last)
{
  for (size_t i = start; i < m_size - (last - start); i++) {
    m_data[i] = m_data[i + (last - start)];
  }
  m_size -= (last - start);
  shrink_if_needed();
}

template<class T>
void vector<T>::push_back(T const& t)
{
  alloc_more_if_needed();
  m_data[m_size] = t;
  m_size++;
}

template<class T>
void vector<T>::emplace_back(T&& t)
{
  alloc_more_if_needed();
  m_data[m_size] = t;
  m_size++;
}

template<class T>
void vector<T>::pop_back()
{
  if (m_size != 0) { m_size--; }
}

template<class T>
void vector<T>::swap(vector<T>& v)
{
  m_data.swap(v.m_data);
  size_t tmp = m_size;
  m_size = v.m_size;
  v.m_size = tmp;
}

template<class T>
void vector<T>::alloc_more_if_needed(size_t room_needed)
{
  if (m_data.size() == 0) {
    m_data.resize(s_first_size + room_needed * 2);
  } else {
    if (m_data.size() * 2 > room_needed) {
      m_data.resize(m_data.size() * 2);
    } else {
      m_data.resize(m_data.size() + (2 * room_needed));
    }
  }
}

template<class T>
void vector<T>::shrink_if_needed()
{
  if (m_size * 4 < m_data.size()) { m_data.resize(m_size * 2); }
}
} // namespace lkcpp