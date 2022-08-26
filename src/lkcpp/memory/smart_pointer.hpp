#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/except/out_of_bounds.hpp"

namespace lkcpp {
template<class T>
class smart_pointer {
public:
  virtual ~smart_pointer() { reset(); }

  T const* get() const { return m_ptr; }
  T& operator*() { return *m_ptr; }
  T const& operator*() const { return *m_ptr; }
  T* operator->() { return m_ptr; }
  T const* operator->() const { return m_ptr; }
  T& operator[](lkcpp::size_t index);
  T const& operator[](lkcpp::size_t index) const;

  bool null() const { return !(bool)m_ptr; }
  operator bool() const { return (bool)m_ptr; }
  lkcpp::size_t size() const { return m_size; }

protected:
  smart_pointer() = default;
  smart_pointer(smart_pointer<T> const&) = default;
  smart_pointer(smart_pointer<T>&&) = default;
  smart_pointer& operator=(smart_pointer<T> const&) = default;
  smart_pointer& operator=(smart_pointer<T>&&) = default;

  smart_pointer(lkcpp::nullptr_t) {}
  smart_pointer(T* ptr, lkcpp::size_t size);

  void reset();
  void reset(T* ptr, lkcpp::size_t size);

private:
  T* m_ptr = nullptr;
  lkcpp::size_t m_size = 0;
};

template<class T>
T& smart_pointer<T>::operator[](lkcpp::size_t index)
{
  if (index >= m_size) {
    throw lkcpp::out_of_bounds_exception(index, 0, m_size - 1);
  }
  return m_t[index];
}

template<class T>
T const& smart_pointer<T>::operator[](lkcpp::size_t index) const
{
  if (index >= m_size) {
    throw lkcpp::out_of_bounds_exception(index, 0, m_size - 1);
  }
  return m_t[index];
}

template<class T>
smart_pointer<T>::smart_pointer(T* ptr, lkcpp::size_t size) :
    m_ptr(ptr), m_size(size)
{}

template<class T>
void smart_pointer<T>::reset()
{
  m_ptr = nullptr;
  m_size = 0;
}

template<class T>
void smart_pointer<T>::reset(T* ptr, lkcpp::size_t size)
{
  m_ptr = ptr;
  m_size = size;
}
} // namespace lkcpp

template<class T>
inline bool operator==(lkcpp::smart_pointer<T> const& lhs,
                       lkcpp::smart_pointer<T> const& rhs)
{
  return lhs.get() == rhs.get();
}

template<class T>
inline bool operator!=(lkcpp::smart_pointer<T> const& lhs,
                       lkcpp::smart_pointer<T> const& rhs)
{
  return !(lhs.get() == rhs.get());
}