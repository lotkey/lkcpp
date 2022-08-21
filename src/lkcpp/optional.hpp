#pragma once

#include "lkcpp/memory/unique_ptr.hpp"
#include "lkcpp/utility/move.hpp"

namespace lkcpp {
template<class T>
class optional {
public:
  optional() = default;
  optional(T&& t);
  optional(optional<T> const& other);
  optional(optional<T>&&) = default;
  optional<T>& operator=(optional<T> const& other);
  optional<T>& operator=(optional<T>&& other);
  virtual ~optional() = default;

  T* operator->();
  T const* operator->() const;
  operator bool() const;
  bool has_value() const;
  T& value();
  T const& value() const;

  void reset();
  template<class... Args>
  void emplace(Args&&... args);

private:
  lkcpp::unique_ptr<T> m_t;
};

template<class T>
optional<T>::optional(T&& t) : m_t(lkcpp::unique_ptr<T>::make(t))
{}

template<class T>
optional<T>::optional(optional<T> const& other)
{
  if (other) { m_t = lkcpp::unique_ptr<T>::make(*other.m_t); }
}

template<class T>
optional<T>& optional<T>::operator=(optional<T> const& other)
{
  m_t.reset();
  if (other) { m_t = lkcpp::unique_ptr<T>::make(*other.m_t); }
}

template<class T>
optional<T>& optional<T>::operator=(optional<T>&& other)
{
  m_t = lkcpp::move(other.m_t);
}

template<class T>
T* optional<T>::operator->()
{
  return m_t.get();
}

template<class T>
T const* optional<T>::operator->() const
{
  return m_t.get();
}

template<class T>
operator optional<T>::bool() const
{
  return (bool)m_t;
}

template<class T>
bool optional<T>::has_value() const
{
  return (bool)m_t;
}

template<class T>
T& optional<T>::value()
{
  return *m_t;
}

template<class T>
T const& optional<T>::value() const
{
  return *m_t;
}

template<class T>
void optional<T>::reset()
{
  m_t.reset();
}

template<class T>
template<class... Args>
void optional<T>::emplace(Args&&... args)
{
  m_t = lkcpp::unique_ptr<T>::make(args...);
}
} // namespace lkcpp