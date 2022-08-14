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
/// "Constructs" a fundamental type from an optional value
/// @param t Pointer to fundamental
/// @param value Value to set the fundamental to
template<class T>
std::enable_if_t<std::is_fundamental_v<T>> construct(T* t, T value = 0)
{
  *t = value;
}

/// Constructs an object with emplacement new and the provided arguments
/// @param t Pointer to object
/// @param args Arguments to provide to the constructor
template<class T, class... Args>
std::enable_if_t<!std::is_fundamental_v<T>> construct(T* t, Args&&... args)
{
  new (t) T(args...);
}

/// "Destructs" a fundamental type by setting it to 0
/// @param t Pointer to fundamental
template<class T>
std::enable_if_t<std::is_fundamental_v<T>> destruct(T* t)
{
  *t = 0;
}

/// Explicitly calls the destructor of an object
/// @param t Pointer to object to destruct
template<class T>
std::enable_if_t<!std::is_fundamental_v<T>> destruct(T* t)
{
  t->~T();
}
} // namespace lkcpp