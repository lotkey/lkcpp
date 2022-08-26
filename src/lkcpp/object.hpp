////////////////////////////////////////////////////////////////////////////////
/// For constructing and destructing objects in place
///
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"

#include <type_traits>

namespace lkcpp {
/// Constructs an object with emplacement new and the provided arguments
/// @param t Pointer to object
/// @param args Arguments to provide to the constructor
template<class T, class... Args>
void construct(T* t, Args&&... args)
{
  new (t) T(args...);
}

/// "Destructs" a fundamental type, does nothing
template<class T>
std::enable_if_t<std::is_fundamental_v<T>> destruct(T*)
{}

/// Explicitly calls the destructor of an object
/// @param t Pointer to object to destruct
template<class T>
std::enable_if_t<!std::is_fundamental_v<T>> destruct(T* t)
{
  t->~T();
}

template<class T1, class T2>
bool is(T1 const& t1, T2 const& t2)
{
  return static_cast<void const*>(&t1) == static_cast<void const*>(&t2);
}
} // namespace lkcpp