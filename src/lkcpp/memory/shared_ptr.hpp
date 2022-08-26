#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/memory/alloc.hpp"

namespace lkcpp {
template<class T>
class shared_ptr {
public:
  template<class... Args>
  static shared_ptr<T> make(Args&&... args);
  template<class... Args>
  static shared_ptr<T>::make_array(lkcpp::size_t size, Args&&... args);

  shared_ptr() = default;

  shared_ptr(T* t, lkcpp::size_t size = 1);
  shared_ptr(shared_ptr<T> const& other);
  shared_ptr(shared_ptr<T>&& other) = default;
  shared_ptr& operator=(shared_ptr<T> const& other);
  shared_ptr& operator=(shared_ptr<T>&& other);
  virtual ~shared_ptr();

  T const* get() const;
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

  void remove_reference();
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
shared_ptr<T> shared_ptr<T>::make_array(std::size_t size, Args&&... args)
{
  T* t = lkcpp::alloc_objs<T>(size, args...);
  return shared_ptr<T>(t);
}

template<class T>
shared_ptr<T>::shared_ptr(T* t, lkcpp::size_t size) :
    m_t(t), m_size(size), m_ref_count(lkcpp::alloc_obj<lkcpp::size_t>())
{}

template<class T>
shared_ptr<T>::shared_ptr(shared_ptr<T> const& other) :
    m_t(other.m_t), m_ref_count(other.m_ref_count), m_size(other.m_size)
{
  if (m_ref_count) { (*m_ref_count)++; }
}

template<class T>
shared_ptr& shared_ptr<T>::operator=(shared_ptr<T> const& other)
{
  remove_reference();
  m_ref_count = other.m_ref_count;
  m_t = other.m_t;
  m_size = other.m_size;
}

template<class T>
shared_ptr& shared_ptr<T>::operator=(shared_ptr<T>&& other) :
    m_t(other.m_t), m_size(other.m_size), m_ref_count(other.m_ref_count)
{
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
bool operator==(lkcpp::shared_ptr<T> const& lhs,
                lkcpp::shared_ptr<T> const& rhs);

template<class T>
inline bool operator!=(lkcpp::shared_ptr<T> const& lhs,
                       lkcpp::shared_ptr<T> const& rhs)
{
  return !(lhs == rhs);
}