////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once
#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/utility.hpp"

#include <iostream>

namespace lkcpp {
/// Smart pointer that takes ownership of memory and frees it upon destruction
/// Modeled after std::unique_ptr
template<class T>
class unique_ptr {
public:
  /// Points to nullptr
  unique_ptr() = default;
  /// Disable copying ownership
  unique_ptr(unique_ptr<T> const&) = delete;
  /// Disable copying ownership
  unique_ptr<T>& operator=(unique_ptr<T> const&) = delete;

  /// Construct from nullptr
  unique_ptr(lkcpp::nullptr_t) {}
  /// Takes ownership of a pointer
  /// @param ptr Pointer to take ownership of
  /// @param size Number of elements allocated
  unique_ptr(T* ptr, size_t size = 1) : m_ptr(ptr), m_size(size) {}
  /// Takes ownership of ptr's memory
  /// @param ptr Temporary unique_ptr
  unique_ptr(unique_ptr<T>&& ptr);
  /// Takes ownership of rvalue
  /// @param ptr Temporary unique_ptr
  unique_ptr<T>& operator=(unique_ptr<T>&& ptr);
  /// Frees any memory that it owns
  virtual ~unique_ptr();

  /// Releases ownership of the memory and returns a pointer to it
  T* release();
  /// Frees any owned memory and points to nullptr
  void reset();
  /// Frees any owned memory and takes ownership of the provided pointer
  /// @param ptr Pointer to take ownership of
  /// @param size Number of elements allocated
  void reset(T* ptr, size_t size = 1);
  /// Swaps memory with another unique_ptr
  /// @param other unique_ptr to swap memory with
  void swap(unique_ptr<T>& other);

  /// @returns Pointer to owned memory
  T* get() { return m_ptr; }
  /// @returns Const pointer to owned memory
  T const* get() const { return m_ptr; }
  /// @returns True if it owns memory
  operator bool() const { return m_ptr; }
  /// @returns The number of elements in the memory owned
  size_t size() const { return m_size; }

  /// Dereference operator
  /// @returns Reference to owned memory
  T& operator*() { return *m_ptr; }
  /// Const dereference operator
  /// @returns Const reference to owned memory
  T const& operator*() const { return *m_ptr; }
  /// @returns Pointer to memory managed by the unique_ptr
  T* operator->() { return m_ptr; }
  /// @returns Const pointer to memory managed by the unique_ptr
  T const* operator->() const { return m_ptr; }

  /// Indexes the owned memory like an array
  /// @returns Reference to the element at the provided index
  T& operator[](size_t index) { return m_ptr[index]; }
  /// Indexes the owned memory like an array
  /// @returns Const reference to the element at the provided index
  T const& operator[](size_t index) const { return m_ptr[index]; }

  /// @returns True if both unique_ptrs own the same memory (this will
  /// result in a double-free).
  bool operator==(unique_ptr<T> const& other) const;
  /// @returns True if the unique_ptrs own different memory.
  bool operator!=(unique_ptr<T> const& other) const;
  /// @returns True if the address is greater than the other pointer's address
  bool operator>(unique_ptr<T> const& other) const;
  /// @returns True if the address is less than the other pointer's address
  bool operator<(unique_ptr<T> const& other) const;
  /// @returns True if the address is greater than or equal the other pointer's
  /// address
  bool operator>=(unique_ptr<T> const& other) const;
  /// @returns True if the address is less than or equal the other pointer's
  /// address
  bool operator<=(unique_ptr<T> const& other) const;

  /// Outputs a pointer to a stream
  friend std::ostream& operator<<(std::ostream& os,
                                  lkcpp::unique_ptr<T> const& x)
  {
    return (os << x.get());
  }

private:
  /// Frees any memory owned by the pointer
  void free_memory();

  T* m_ptr = nullptr;
  size_t m_size = 0;
};

/// Allocates an object on the heap and returns a unique_ptr to the object
template<class T, class... Args>
unique_ptr<T> make_unique(Args&&... args)
{
  T* ptr = new T(args...);
  return unique_ptr<T>(ptr);
}

/// Allocates an array on the heap and returns a unique_ptr to the array
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