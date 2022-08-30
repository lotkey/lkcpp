#pragma once

#include "lkcpp/tuple.hpp"

namespace lkcpp {
// template<class T1, class T2>
// class pair : public tuple<T1, T2> {
// public:
//   pair() = default;
//   pair(pair<T1, T2> const&) = default;
//   pair(pair<T1, T2>&&) = default;
//   pair& operator=(pair<T1, T2> const&) = default;
//   pair& operator=(pair<T1, T2>&&) = default;
//   virtual ~pair() = default;

//   pair(T1&& t1, T2&& t2);

//   // T1& first() { return m_tup.get<0>(); }
//   // T1 const& first() const { return tuple<T1, T2>::get<0>(); }
//   // T2& second() { return tuple<T1, T2>::get<1>(); }
//   // T2 const& second() const { return tuple<T1, T2>::get<1>(); }
//   // private:
//   //   tuple<T1, T2> m_tup;
// };

// template<class T1, class T2>
// pair<T1, T2>::pair(T1&& t1, T2&& t2) : tuple<T1, T2>(t1, t2)
// {}
class pair : public lkcpp::tuple<int, int> {
public:
  auto& first() { return get<0>(); }
  auto first() const { return get<0>(); }

private:
};
} // namespace lkcpp