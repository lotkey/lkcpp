#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/except/out_of_bounds.hpp"
#include "lkcpp/utility/move.hpp"
#include "lkcpp/utility/remove_reference.hpp"

namespace lkcpp {
namespace {
template<lkcpp::size_t Index, class T>
class tuple_impl {
public:
  tuple_impl() = default;
  tuple_impl(T const& t) : m_t(t) {}
  tuple_impl(T&& t) : m_t(lkcpp::move(t)) {}

  T& get() { return m_t; }
  T const& get() const { return m_t; }

private:
  T m_t;
};

template<lkcpp::size_t Index, class... Args>
class tuple_base {};

template<lkcpp::size_t Index, class T, class... Args>
class tuple_base<Index, T, Args...> :
    public tuple_impl<Index, typename lkcpp::remove_reference<T>::type>,
    public tuple_base<Index + 1, Args...> {};

template<lkcpp::size_t Index, class T, class... Args>
struct extract_type_at {
  using type = typename extract_type_at<Index - 1, Args...>::type;
};

template<class T, class... Args>
struct extract_type_at<0, T, Args...> {
  using type = T;
};

template<class... Args>
struct arg_count;

template<class T, class... Args>
struct arg_count<T, Args...> {
  static constexpr lkcpp::size_t count = 1 + arg_count<Args...>::count;
};

template<>
struct arg_count<> {
  static constexpr lkcpp::size_t count = 0;
};
} // namespace

template<class T, class... Args>
class tuple : public tuple_base<0, T, Args...> {
public:
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

  constexpr lkcpp::size_t size() const { return arg_count<T, Args...>(); }
};
} // namespace lkcpp