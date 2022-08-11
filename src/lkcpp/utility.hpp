#pragma once

namespace lkcpp {
template<class T>
T&& move(T&& t)
{
  return t;
}
} // namespace lkcpp