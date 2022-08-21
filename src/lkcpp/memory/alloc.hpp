////////////////////////////////////////////////////////////////////////////////
/// Provides control over how objects/data are allocated/deallocated
///
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/except/failed_allocation.hpp"
#include "lkcpp/object.hpp"

#include <cstdlib>
#include <iostream>

namespace lkcpp {
template<class T>
T* alloc(lkcpp::size_t size = 1);
template<class T>
T* realloc(T* t, lkcpp::size_t size);
template<class T>
void dealloc(T* t);

template<class T, class... Args>
T* alloc_obj(Args&&... args);
template<class T, class... Args>
T* alloc_objs(lkcpp::size_t size, Args&&...);
template<class T, class... Args>
T* realloc_objs(T* t,
                lkcpp::size_t original_size,
                lkcpp::size_t size,
                Args&&... args);
template<class T>
void dealloc_obj(T* t);
template<class T>
void dealloc_objs(T* t, lkcpp::size_t size);

/// Allocates data from the heap
/// @tparam T Type of elements to allocate
/// @param size Number of T elements to allocate
template<class T>
T* alloc(lkcpp::size_t size)
{
  return static_cast<T*>(lkcpp::alloc<void>(sizeof(T) * size));
}

template<>
void* alloc(lkcpp::size_t size);

/// Reallocates data on the heap
/// @param t Pointer to data to reallocate
/// @param size Number of elements to reallocate
template<class T>
T* realloc(T* t, lkcpp::size_t size)
{
  return static_cast<T*>(
    lkcpp::realloc(static_cast<void*>(t), sizeof(T) * size));
}

template<>
void* realloc(void* t, lkcpp::size_t size);

/// Deallocates data on the heap
/// @param t Pointer to data to deallocate
template<class T>
void dealloc(T* t)
{
  if (t == nullptr) { return; }
  free(t);
}

/// Allocates and constructs an object on the heap
/// @tparam T Type of object to construct
/// @param args Arguments to pass to the constructor
template<class T, class... Args>
T* alloc_obj(Args&&... args)
{
  T* t = lkcpp::alloc<T>();
  lkcpp::construct(t, args...);
  return t;
}

/// Allocates and constructs multiple objects on the heap
/// @tparam T Type of objects to construct
/// @param size Number of objects to construct
/// @param args Arguments to pass to the constructor of all objects being
/// constructed
template<class T, class... Args>
T* alloc_objs(lkcpp::size_t size, Args&&... args)
{
  T* t = lkcpp::alloc<T>(size);
  for (lkcpp::size_t i = 0; i < size; i++) { construct(t + i, args...); }
  return t;
}

/// Reallocates objects on the heap, destructing any that may go out of bounds
/// @param t Pointer to objects to reallocate
/// @param size Number of elements to reallocate t to
template<class T, class... Args>
T* realloc_objs(T* t,
                lkcpp::size_t original_size,
                lkcpp::size_t size,
                Args&&... args)
{
  if (size == 0) {
    lkcpp::dealloc_objs(t, original_size);
    return nullptr;
  }

  for (lkcpp::size_t i = size; i < original_size; i++) {
    lkcpp::destruct(t + i);
  }

  t = lkcpp::realloc(t, size);
  for (std::size_t i = original_size; i < size; i++) {
    lkcpp::construct(t + i, args...);
  }
  return t;
}

template<class T>
void dealloc_obj(T* t)
{
  if (t == nullptr) { return; }
  lkcpp::destruct(t);
  lkcpp::dealloc(t);
}

/// Deallocates objects on the heap, destructing them in the process
/// @param t Pointer to objects to deallocate
template<class T>
void dealloc_objs(T* t, lkcpp::size_t size)
{
  if (t == nullptr) { return; }
  for (lkcpp::size_t i = 0; i < size; i++) { lkcpp::destruct(t + i); }
  lkcpp::dealloc(t);
}
} // namespace lkcpp