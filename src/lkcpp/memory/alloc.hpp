////////////////////////////////////////////////////////////////////////////////
/// Provides control over how objects/data are allocated/deallocated
///
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/object.hpp"

#include <cstdlib>

namespace lkcpp {
template<class T>
T* alloc(size_t size = 1);
template<class T>
T* realloc(T* t, size_t size);
template<class T>
void dealloc(T* t);

template<class T, class... Args>
T* alloc_obj(Args&&... args);
template<class T, class... Args>
T* alloc_objs(size_t size, Args&&...);
template<class T>
T* realloc_objs(T* t, size_t size);
template<class T>
void dealloc_objs(T* t);

/// Allocates data from the heap
/// @tparam T Type of elements to allocate
/// @param size Number of T elements to allocate
template<class T>
T* alloc(size_t size)
{
  size_t* p =
    static_cast<size_t*>(std::malloc(sizeof(size_t) + (sizeof(T) * size)));
  *p = size;
  return static_cast<T*>(static_cast<void*>(p + 1));
}

template<>
void* alloc(size_t size);

/// Reallocates data on the heap
/// @param t Pointer to data to reallocate
/// @param size Number of elements to reallocate
template<class T>
T* realloc(T* t, size_t size)
{
  size_t* p = static_cast<size_t*>(static_cast<void*>(t)) - 1;
  size_t* new_data =
    static_cast<size_t*>(std::realloc(p, sizeof(size_t) + (sizeof(T) * size)));
  return static_cast<T*>(static_cast<void*>(new_data + 1));
}

template<>
void* realloc(void* t, size_t size);

/// Deallocates data on the heap
/// @param t Pointer to data to deallocate
template<class T>
void dealloc(T* t)
{
  if (t == nullptr) { return; }
  size_t* p = static_cast<size_t*>(static_cast<void*>(t)) - 1;
  free(p);
}

/// Allocates and constructs an object on the heap
/// @tparam T Type of object to construct
/// @param args Arguments to pass to the constructor
template<class T, class... Args>
T* alloc_obj(Args&&... args)
{
  T* t = lkcpp::alloc<T>();
  construct(t, args...);
  return t;
}

/// Allocates and constructs multiple objects on the heap
/// @tparam T Type of objects to construct
/// @param size Number of objects to construct
/// @param args Arguments to pass to the constructor of all objects being
/// constructed
template<class T, class... Args>
T* alloc_objs(size_t size, Args&&... args)
{
  T* t = lkcpp::alloc<T>(size);
  for (size_t i = 0; i < size; i++) { construct(t + i, args...); }
  size_t* p = static_cast<size_t*>(static_cast<void*>(t)) - 1;
  *p = size;
  return t;
}

/// Reallocates objects on the heap, destructing any that may go out of bounds
/// @param t Pointer to objects to reallocate
/// @param size Number of elements to reallocate t to
template<class T>
T* realloc_objs(T* t, size_t size)
{
  size_t* p = static_cast<size_t*>(static_cast<void*>(t)) - 1;

  if (*p > size) {
    for (size_t i = size; i < *p; i++) { destruct(t + i); }
  }
  return realloc(t, size);
}

/// Deallocates objects on the heap, destructing them in the process
/// @param t Pointer to objects to deallocate
template<class T>
void dealloc_objs(T* t)
{
  size_t num_elems = *(static_cast<size_t*>(static_cast<void*>(t)) - 1);
  for (size_t i = 0; i < num_elems; i++) { destruct(t + i); }
  lkcpp::dealloc(t);
}
} // namespace lkcpp