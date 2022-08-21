////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/utility/remove_reference.hpp"

namespace lkcpp {
/// Used to indicate an rvalue
/// Modeled after std::move
template<class T>
typename remove_reference<T>::type&& move(T&& t)
{
  return static_cast<remove_reference<T>::type&&>(t);
}
} // namespace lkcpp