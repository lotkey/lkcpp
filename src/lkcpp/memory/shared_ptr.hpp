#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/except/out_of_bounds.hpp"
#include "lkcpp/memory/alloc.hpp"

namespace lkcpp {
template<class T>
class weak_ptr;

template<class T>
class shared_ptr {
public:
  template<class... Args>
  static shared_ptr<T> make(Args&&... args);
  template<class... Args>
  static shared_ptr<T> make_array(lkcpp::size_t size, Args&&... args);

  shared_ptr() = default;

  shared_ptr(T* t, lkcpp::size_t size = 1);
  shared_ptr(shared_ptr<T> const& other);
  shared_ptr(shared_ptr<T>&& other) = default;
  shared_ptr<T>& operator=(shared_ptr<T> const& other);
  shared_ptr<T>& operator=(shared_ptr<T>&& other);
  virtual ~shared_ptr();

  T const* get() const;
  lkcpp::size_t size() const;
  T& operator*();
  T const& operator*() const;
  T* operator->();
  T const* operator->() const;
  T& operator[](lkcpp::size_t index);
  T const& operator[](lkcpp::size_t index) const;
  lkcpp::size_t use_count() const;
  bool unique() const;
  operator bool() const;

  void reset();
  void reset(T* t, size_t size = 1);

private:
  T* m_t = nullptr;
  lkcpp::size_t* m_ref_count = nullptr;
  lkcpp::size_t m_size = 0;

  shared_ptr(T* t, lkcpp::size_t size, lkcpp::size_t* ref_count);
  void remove_reference();

  friend class weak_ptr<T>;
};

template<class T>
template<class... Args>
shared_ptr<T> shared_ptr<T>::make(Args&&... args)
{
  T* t = lkcpp::alloc_obj<T>(args...);
  return shared_ptr<T>(t);
}

template<class T>
template<class... Args>
shared_ptr<T> shared_ptr<T>::make_array(lkcpp::size_t size, Args&&... args)
{
  T* t = lkcpp::alloc_objs<T>(size, args...);
  return shared_ptr<T>(t);
}

template<class T>
shared_ptr<T>::shared_ptr(T* t, lkcpp::size_t size) :
    m_t(t), m_size(size), m_ref_count(lkcpp::alloc_obj<lkcpp::size_t>(1))
{}

template<class T>
shared_ptr<T>::shared_ptr(shared_ptr<T> const& other) :
    m_t(other.m_t), m_ref_count(other.m_ref_count), m_size(other.m_size)
{
  if (m_ref_count) { (*m_ref_count)++; }
}

template<class T>
shared_ptr<T>::shared_ptr(T* t, lkcpp::size_t size, lkcpp::size_t* ref_count) :
    m_t(t), m_size(size), m_ref_count(ref_count)
{
  if (m_ref_count) { (*m_ref_count)++; }
}

template<class T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T> const& other)
{
  remove_reference();
  m_ref_count = other.m_ref_count;
  m_t = other.m_t;
  m_size = other.m_size;
}

template<class T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& other)
{
  m_t = other.m_t;
  m_size = other.m_size;
  m_ref_count = other.m_ref_count;
  other.m_t = nullptr;
  other.m_size = 0;
  other.m_ref_count = nullptr;
}

template<class T>
shared_ptr<T>::~shared_ptr()
{
  remove_reference();
}

template<class T>
inline T const* shared_ptr<T>::get() const
{
  return m_t;
}

template<class T>
inline lkcpp::size_t shared_ptr<T>::size() const
{
  return m_size;
}

template<class T>
inline T& shared_ptr<T>::operator*()
{
  return *m_t;
}

template<class T>
inline T const& shared_ptr<T>::operator*() const
{
  return *m_t;
}

template<class T>
inline T* shared_ptr<T>::operator->()
{
  return m_t;
}

template<class T>
inline T const* shared_ptr<T>::operator->() const
{
  return m_t;
}

template<class T>
T& shared_ptr<T>::operator[](lkcpp::size_t index)
{
  if (index >= m_size) {
    throw lkcpp::out_of_bounds_exception(index, 0, m_size - 1);
  }
  return m_t[index];
}

template<class T>
T const& shared_ptr<T>::operator[](lkcpp::size_t index) const
{
  if (index >= m_size) {
    throw lkcpp::out_of_bounds_exception(index, 0, m_size - 1);
  }
  return m_t[index];
}

template<class T>
lkcpp::size_t shared_ptr<T>::use_count() const
{
  if (m_ref_count) {
    return *m_ref_count;
  } else {
    return 0;
  }
}

template<class T>
inline bool shared_ptr<T>::unique() const
{
  return use_count() == 1;
}

template<class T>
inline shared_ptr<T>::operator bool() const
{
  return m_t;
}

template<class T>
void shared_ptr<T>::remove_reference()
{
  if (m_ref_count) {
    (*m_ref_count)--;
    if (*m_ref_count == 0) {
      lkcpp::dealloc_objs(m_t, m_size);
      m_t = nullptr;
      m_size = 0;
      lkcpp::dealloc(m_ref_count);
      m_ref_count = nullptr;
    }
  }
}
} // namespace lkcpp

template<class T>
inline bool operator==(lkcpp::shared_ptr<T> const& lhs,
                       lkcpp::shared_ptr<T> const& rhs)
{
  return lhs.get() == rhs.get();
}

template<class T>
inline bool operator!=(lkcpp::shared_ptr<T> const& lhs,
                       lkcpp::shared_ptr<T> const& rhs)
{
  return !(lhs == rhs);
}