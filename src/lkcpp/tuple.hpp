////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/except/out_of_bounds.hpp"
#include "lkcpp/utility/move.hpp"
#include "lkcpp/utility/remove_reference.hpp"

namespace lkcpp {
namespace {
template<lkcpp::size_t Index, class T>
class tuple_impl;

template<lkcpp::size_t Index, class... Args>
class tuple_base;

template<lkcpp::size_t Index, class T, class... Args>
struct extract_type_at;

template<class... Args>
struct arg_count;
} // namespace

template<class T, class... Args>
class tuple : private tuple_base<0, T, Args...> {
public:
  static tuple<T, Args...> make();
  static tuple<T, Args...> make(T&& t, Args&&... args);

  tuple() = default;
  tuple(tuple<T, Args...> const& other) = default;
  tuple(tuple<T, Args...>&& other) = default;
  tuple& operator=(tuple<T, Args...> const& other) = default;
  tuple& operator=(tuple<T, Args...>&& other) = default;
  virtual ~tuple() = default;

  tuple(T&& t, Args&&... args);

  template<lkcpp::size_t Index>
  auto& get()
  {
    return static_cast<
             tuple_impl<Index,
                        typename extract_type_at<Index, T, Args...>::type>&>(
             *this)
      .get();
  }
  template<lkcpp::size_t Index>
  auto const& get() const
  {
    return static_cast<tuple_impl<
      Index,
      typename extract_type_at<Index, T, Args...>::type> const&>(*this)
      .get();
  }

  constexpr lkcpp::size_t size() const;

  friend bool operator==(tuple<T, Args...> const& t1,
                         tuple<T, Args...> const& t2)
  {
    return static_cast<base const&>(t1) == static_cast<base const&>(t2);
  }

  friend bool operator!=(tuple<T, Args...> const& t1,
                         tuple<T, Args...> const& t2)
  {
    return static_cast<base const&>(t1) != static_cast<base const&>(t2);
  }

  friend bool operator>(tuple<T, Args...> const& t1,
                        tuple<T, Args...> const& t2)
  {
    return static_cast<base const&>(t1) > static_cast<base const&>(t2);
  }

  friend bool operator<(tuple<T, Args...> const& t1,
                        tuple<T, Args...> const& t2)
  {
    return static_cast<base const&>(t1) < static_cast<base const&>(t2);
  }

  friend bool operator>=(tuple<T, Args...> const& t1,
                         tuple<T, Args...> const& t2)
  {
    return static_cast<base const&>(t1) >= static_cast<base const&>(t2);
  }

  friend bool operator<=(tuple<T, Args...> const& t1,
                         tuple<T, Args...> const& t2)
  {
    return static_cast<base const&>(t1) <= static_cast<base const&>(t2);
  }

private:
  using base = tuple_base<0, T, Args...>;
};

template<class T, class... Args>
inline tuple<T, Args...> tuple<T, Args...>::make()
{
  return tuple<T, Args...>();
}

template<class T, class... Args>
inline tuple<T, Args...> tuple<T, Args...>::make(T&& t, Args&&... args)
{
  return tuple<T, Args...>(lkcpp::move(t), lkcpp::move(args)...);
}

template<class T, class... Args>
tuple<T, Args...>::tuple(T&& t, Args&&... args) :
    base(lkcpp::move(t), lkcpp::move(args)...)
{}

template<class T, class... Args>
constexpr lkcpp::size_t tuple<T, Args...>::size() const
{
  return arg_count<T, Args...>::count;
}

namespace {
template<lkcpp::size_t Index, class T>
class tuple_impl {
public:
  tuple_impl() = default;
  tuple_impl(tuple_impl<Index, T> const&) = default;
  tuple_impl(tuple_impl<Index, T>&&) = default;
  tuple_impl& operator=(tuple_impl<Index, T> const&) = default;
  tuple_impl& operator=(tuple_impl<Index, T>&&) = default;
  virtual ~tuple_impl() = default;

  tuple_impl(T const& t);
  tuple_impl(T&& t);

  T& get();
  T const& get() const;

  bool operator==(tuple_impl<Index, T> const& other) const;
  bool operator!=(tuple_impl<Index, T> const& other) const;
  bool operator>(tuple_impl<Index, T> const& other) const;
  bool operator<(tuple_impl<Index, T> const& other) const;
  bool operator>=(tuple_impl<Index, T> const& other) const;
  bool operator<=(tuple_impl<Index, T> const& other) const;

private:
  T m_t;
};

template<lkcpp::size_t Index, class... Args>
class tuple_base {
public:
  bool operator==(tuple_base<Index, Args...> const&) const { return true; }
  bool operator!=(tuple_base<Index, Args...> const&) const { return false; }
  bool operator>(tuple_base<Index, Args...> const&) const { return false; }
  bool operator<(tuple_base<Index, Args...> const&) const { return false; }
  bool operator>=(tuple_base<Index, Args...> const&) const { return true; }
  bool operator<=(tuple_base<Index, Args...> const&) const { return true; }
};

template<lkcpp::size_t Index, class T, class... Args>
class tuple_base<Index, T, Args...> :
    public tuple_impl<Index, typename lkcpp::remove_reference<T>::type>,
    public tuple_base<Index + 1, Args...> {
public:
  tuple_base() = default;
  tuple_base(tuple_base<Index, T, Args...> const&) = default;
  tuple_base(tuple_base<Index, T, Args...>&&) = default;
  tuple_base<Index, T, Args...>& operator=(
    tuple_base<Index, T, Args...> const&) = default;
  tuple_base<Index, T, Args...>& operator=(tuple_base<Index, T, Args...>&&) =
    default;
  virtual ~tuple_base() = default;

  tuple_base(T&& t, Args&&... args);

  bool operator==(tuple_base<Index, T, Args...> const& other) const;
  bool operator!=(tuple_base<Index, T, Args...> const& other) const;
  bool operator>(tuple_base<Index, T, Args...> const& other) const;
  bool operator<(tuple_base<Index, T, Args...> const& other) const;
  bool operator>=(tuple_base<Index, T, Args...> const& other) const;
  bool operator<=(tuple_base<Index, T, Args...> const& other) const;

private:
  using base_impl =
    tuple_impl<Index, typename lkcpp::remove_reference<T>::type>;
  using base_base = tuple_base<Index + 1, Args...>;
};

template<lkcpp::size_t Index, class T, class... Args>
struct extract_type_at {
  using type = typename extract_type_at<Index - 1, Args...>::type;
};

template<class T, class... Args>
struct extract_type_at<0, T, Args...> {
  using type = T;
};

template<class T, class... Args>
struct arg_count<T, Args...> {
  static constexpr lkcpp::size_t count = 1 + arg_count<Args...>::count;
};

template<>
struct arg_count<> {
  static constexpr lkcpp::size_t count = 0;
};

template<lkcpp::size_t Index, class T>
tuple_impl<Index, T>::tuple_impl(T const& t) : m_t(t)
{}

template<lkcpp::size_t Index, class T>
tuple_impl<Index, T>::tuple_impl(T&& t) : m_t(lkcpp::move(t))
{}

template<lkcpp::size_t Index, class T>
inline T& tuple_impl<Index, T>::get()
{
  return m_t;
}

template<lkcpp::size_t Index, class T>
inline T const& tuple_impl<Index, T>::get() const
{
  return m_t;
}

template<lkcpp::size_t Index, class T>
inline bool tuple_impl<Index, T>::operator==(
  tuple_impl<Index, T> const& other) const
{
  return m_t == other.m_t;
}

template<lkcpp::size_t Index, class T>
inline bool tuple_impl<Index, T>::operator!=(
  tuple_impl<Index, T> const& other) const
{
  return !(*this == other);
}

template<lkcpp::size_t Index, class T>
inline bool tuple_impl<Index, T>::operator>(
  tuple_impl<Index, T> const& other) const
{
  return m_t > other.m_t;
}

template<lkcpp::size_t Index, class T>
inline bool tuple_impl<Index, T>::operator<(
  tuple_impl<Index, T> const& other) const
{
  return m_t < other.m_t;
}

template<lkcpp::size_t Index, class T>
inline bool tuple_impl<Index, T>::operator>=(
  tuple_impl<Index, T> const& other) const
{
  return m_t >= other.m_t;
}

template<lkcpp::size_t Index, class T>
inline bool tuple_impl<Index, T>::operator<=(
  tuple_impl<Index, T> const& other) const
{
  return m_t <= other.m_t;
}

template<lkcpp::size_t Index, class T, class... Args>
tuple_base<Index, T, Args...>::tuple_base(T&& t, Args&&... args) :
    base_impl(lkcpp::move(t)), base_base(lkcpp::move(args)...)
{}

template<lkcpp::size_t Index, class T, class... Args>
inline bool tuple_base<Index, T, Args...>::operator==(
  tuple_base<Index, T, Args...> const& other) const
{
  return base_impl::operator==(other) && base_base::operator==(other);
}

template<lkcpp::size_t Index, class T, class... Args>
inline bool tuple_base<Index, T, Args...>::operator!=(
  tuple_base<Index, T, Args...> const& other) const
{
  return !(*this == other);
}

template<lkcpp::size_t Index, class T, class... Args>
inline bool tuple_base<Index, T, Args...>::operator>(
  tuple_base<Index, T, Args...> const& other) const
{
  return base_impl::operator>(other) || base_base::operator>(other);
}

template<lkcpp::size_t Index, class T, class... Args>
inline bool tuple_base<Index, T, Args...>::operator<(
  tuple_base<Index, T, Args...> const& other) const
{
  return base_impl::operator<(other) || base_base::operator<(other);
}

template<lkcpp::size_t Index, class T, class... Args>
inline bool tuple_base<Index, T, Args...>::operator>=(
  tuple_base<Index, T, Args...> const& other) const
{
  return !base_impl::operator<(other) || !base_base::operator<(other);
}

template<lkcpp::size_t Index, class T, class... Args>
inline bool tuple_base<Index, T, Args...>::operator<=(
  tuple_base<Index, T, Args...> const& other) const
{
  return !base_impl::operator>(other) || !base_base::operator>(other);
}
} // namespace
} // namespace lkcpp