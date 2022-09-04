////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/memory/shared_ptr.hpp"

namespace lkcpp {
/// Non-owning reference to memory owned by shared_ptrs
/// Modeled after std::weak_ptr
template<class T>
class weak_ptr {
public:
  weak_ptr() = default;
  weak_ptr(weak_ptr const&) = default;
  weak_ptr(weak_ptr&&) = default;
  weak_ptr& operator=(weak_ptr const&) = default;
  weak_ptr& operator=(weak_ptr&&) = default;

  /// Copy reference to shared memory
  weak_ptr(lkcpp::shared_ptr<T> const& shared);
  /// Copy reference to shared memory
  weak_ptr(lkcpp::shared_ptr<T>&& shared);
  virtual ~weak_ptr();

  /// Reference nullptr
  void reset();
  /// @returns The number of shared pointers managing the memory
  lkcpp::size_t use_count() const;
  /// @returns A shared pointer that manages the memory
  lkcpp::shared_ptr<T> lock() const;
  T const* get() const;
  lkcpp::size_t size() const;

  T& operator*();
  T const& operator*() const;
  T* operator->();
  T const* operator->() const;

  operator bool() const;

private:
  T* m_t = nullptr;
  lkcpp::size_t* m_ref_count = nullptr;
  lkcpp::size_t m_size = 0;
};

template<class T>
weak_ptr<T>::weak_ptr(lkcpp::shared_ptr<T> const& shared) :
    m_t(shared.m_t), m_ref_count(shared.m_ref_count), m_size(shared.m_size)
{}

template<class T>
weak_ptr<T>::weak_ptr(lkcpp::shared_ptr<T>&& shared) :
    m_t(shared.m_t), m_ref_count(shared.m_ref_count), m_size(shared.m_size)
{}

template<class T>
weak_ptr<T>::~weak_ptr()
{
  reset();
}

template<class T>
void weak_ptr<T>::reset()
{
  m_t = nullptr;
  m_ref_count = nullptr;
  m_size = 0;
}

template<class T>
lkcpp::size_t weak_ptr<T>::use_count() const
{
  if (m_ref_count) {
    return *m_ref_count;
  } else {
    return 0;
  }
}

template<class T>
inline lkcpp::shared_ptr<T> weak_ptr<T>::lock() const
{
  return lkcpp::shared_ptr<T>(m_t, m_size, m_ref_count);
}

template<class T>
inline T const* weak_ptr<T>::get() const
{
  return m_t;
}

template<class T>
inline lkcpp::size_t weak_ptr<T>::size() const
{
  return m_size;
}

template<class T>
inline T& weak_ptr<T>::operator*()
{
  return *m_t;
}

template<class T>
inline T const& weak_ptr<T>::operator*() const
{
  return *m_t;
}

template<class T>
inline T* weak_ptr<T>::operator->()
{
  return m_t;
}

template<class T>
inline T const* weak_ptr<T>::operator->() const
{
  return m_t;
}

template<class T>
inline weak_ptr<T>::operator bool() const
{
  return m_t;
}
} // namespace lkcpp

template<class T>
inline bool operator==(lkcpp::weak_ptr<T> const& lhs,
                       lkcpp::weak_ptr<T> const& rhs)
{
  return lhs.get() == rhs.get();
}

template<class T>
inline bool operator!=(lkcpp::weak_ptr<T> const& lhs,
                       lkcpp::weak_ptr<T> const& rhs)
{
  return !(lhs == rhs);
}