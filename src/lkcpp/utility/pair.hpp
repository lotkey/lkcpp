////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/tuple.hpp"

namespace lkcpp {
/// Pair of elements
/// Modeled after std::tuple
template<class T1, class T2>
class pair : public lkcpp::tuple<T1, T2> {
public:
  pair() = default;
  pair(pair<T1, T2> const&) = default;
  pair(pair<T1, T2>&&) = default;
  pair& operator=(pair<T1, T2> const&) = default;
  pair& operator=(pair<T1, T2>&&) = default;
  virtual ~pair() = default;

  pair(T1&& t1, T2&& t2) :
      lkcpp::tuple<T1, T2>(lkcpp::move(t1), lkcpp::move(t2))
  {}

  /// @returns Reference to the first element
  T1& first() { return lkcpp::tuple<T1, T2>::template get<0>(); }
  /// @returns Const reference to the first element
  T1 const& first() const { return lkcpp::tuple<T1, T2>::template get<0>(); }
  /// @returns Reference to the second element
  T2& second() { return lkcpp::tuple<T1, T2>::template get<1>(); }
  /// @returns Const reference to the second element
  T2 const& second() const { return lkcpp::tuple<T1, T2>::template get<1>(); }
};
} // namespace lkcpp