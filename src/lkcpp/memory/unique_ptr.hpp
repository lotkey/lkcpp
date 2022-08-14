#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/utility.hpp"

#include <iostream>

namespace lkcpp {
template<class T>
class unique_ptr {
public:
  unique_ptr() = default;
  unique_ptr(unique_ptr<T> const&) = delete;
  unique_ptr<T>& operator=(unique_ptr<T> const&) = delete;

  unique_ptr(lkcpp::nullptr_t) {}
  unique_ptr(T* ptr, size_t size = 1) : m_ptr(ptr), m_size(size) {}
  unique_ptr(unique_ptr<T>&& ptr);
  unique_ptr<T>& operator=(unique_ptr<T>&& ptr);
  virtual ~unique_ptr();

  T* release();
  void reset();
  void reset(T* ptr, size_t size = 1);
  void swap(unique_ptr<T>& other);

  T* get() { return m_ptr; }
  T const* get() const { return m_ptr; }
  operator bool() const { return m_ptr; }
  size_t size() const { return m_size; }

  T& operator*() { return *m_ptr; }
  T const& operator*() const { return *m_ptr; }
  T* operator->() { return m_ptr; }
  T const* operator->() const { return m_ptr; }

  T& operator[](size_t index) { return m_ptr[index]; }
  T const& operator[](size_t index) const { return m_ptr[index]; }

  bool operator==(unique_ptr<T> const& other) const;
  bool operator!=(unique_ptr<T> const& other) const;
  bool operator>(unique_ptr<T> const& other) const;
  bool operator<(unique_ptr<T> const& other) const;
  bool operator>=(unique_ptr<T> const& other) const;
  bool operator<=(unique_ptr<T> const& other) const;

private:
  void free_memory();

  T* m_ptr = nullptr;
  size_t m_size = 0;
};

template<class T, class... Args>
unique_ptr<T> make_unique(Args&&... args)
{
  T* ptr = new T(args...);
  return unique_ptr<T>(ptr);
}

template<class T>
unique_ptr<T> make_unique_array(size_t size)
{
  T* ptr = new T[size];
  return unique_ptr<T>(ptr, size);
}

template<class T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& ptr) :
    m_ptr(ptr.release()), m_size(ptr.m_size)
{
  ptr.m_size = 0;
}

template<class T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& ptr)
{
  m_ptr = ptr.release();
  m_size = ptr.m_size;
  ptr.m_size = 0;
}

template<class T>
unique_ptr<T>::~unique_ptr()
{
  free_memory();
}

template<class T>
T* unique_ptr<T>::release()
{
  T* tmp = m_ptr;
  m_ptr = nullptr;
  m_size = 0;
  return tmp;
}

template<class T>
void unique_ptr<T>::reset()
{
  free_memory();
}

template<class T>
void unique_ptr<T>::reset(T* ptr, size_t size)
{
  free_memory();
  m_ptr = ptr;
  m_size = size;
}

template<class T>
void unique_ptr<T>::swap(unique_ptr<T>& other)
{
  lkcpp::swap(m_ptr, other.m_ptr);
  lkcpp::swap(m_size, other.m_size);
}

template<class T>
bool unique_ptr<T>::operator==(unique_ptr<T> const& other) const
{
  return get() == other.get();
}

template<class T>
bool unique_ptr<T>::operator!=(unique_ptr<T> const& other) const
{
  return get() != other.get();
}

template<class T>
bool unique_ptr<T>::operator<(unique_ptr<T> const& other) const
{
  return get() < other.get();
}

template<class T>
bool unique_ptr<T>::operator<=(unique_ptr<T> const& other) const
{
  return get() <= other.get();
}

template<class T>
bool unique_ptr<T>::operator>(unique_ptr<T> const& other) const
{
  return get() > other.get();
}

template<class T>
bool unique_ptr<T>::operator>=(unique_ptr<T> const& other) const
{
  return get() >= other.get();
}

template<class T>
void unique_ptr<T>::free_memory()
{
  if (!m_ptr) { return; }
  if (m_size == 1) {
    delete m_ptr;
  } else {
    delete[] m_ptr;
  }
  m_ptr = nullptr;
  m_size = 0;
}
} // namespace lkcpp

template<class T>
std::ostream& operator<<(std::ostream& os, lkcpp::unique_ptr<T> const& x)
{
  return (os << x.get());
}