////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/memory.hpp"

#include <iostream>

namespace lkcpp {
/// Resizable chunk of POD (plain-old-data)
class pod {
public:
  pod() = default;

  /// Allocate a chunk of POD and zero it
  /// @param size Size of POD in bytes
  pod(size_t size);
  /// Allocate a chunk of POD and copy from buffer
  /// @param buffer Buffer to copy data from
  /// @param size Size of POD in T elements
  template<class T>
  pod(T const* buffer, size_t size);
  /// Deep copy a POD
  pod(pod const& other);
  /// Construct from POD rvalue
  pod(pod&& other);
  /// Deep copy a POD
  pod& operator=(pod const& other);
  /// Assign from POD rvalue
  pod& operator=(pod&& other);
  /// Deallocate any owner memory
  virtual ~pod();

  /// Empty the pod and deallocate the memory
  void clear();
  /// Swap PODs
  void swap(pod& other);
  /// Expand or contract the pod
  /// Expanding includes zero-ing any new memory
  /// @param size Size to resize the POD to
  void resize(size_t size);
  /// @return True if contents of the PODs are exactly the same
  bool operator==(pod const& other) const;
  /// @return False if contents of the PODs are exactly the same
  bool operator!=(pod const& other) const;

  /// @returns Size of the POD in bytes
  size_t size() const;
  /// @returns True if the POD size is 0
  bool empty() const;
  /// @returns Pointer to data
  void* data();
  /// @returns Const pointer to data
  void const* data() const;
  /// @returns Char pointer to data
  char* bytes();
  /// @returns Const char pointer to data
  char const* bytes() const;
  /// @returns A reference to the byte at some index
  /// @param index Index to get reference to
  char& at(size_t index);
  /// @returns A copy of the byte at some index
  /// @param index Index to get reference to
  char at(size_t index) const;
  /// @returns A reference to the byte at some index
  /// @param index Index to get reference to
  char& operator[](size_t index);
  /// @returns A copy of the byte at some index
  /// @param index Index to get reference to
  char operator[](size_t index) const;
  /// @returns A reference to the first byte in the POD
  char& front();
  /// @returns A copy of the first byte in the POD
  char front() const;
  /// @returns A reference to the last byte in the POD
  char& back();
  /// @returns A copy of the last byte in the POD
  char back() const;

  /// Shift the entire pod to the right, wrapping around to the front
  pod& operator>>(size_t num_shifts);
  /// Shift the entire pod to the left, wrapping around to the back
  pod& operator<<(size_t num_shifts);

  /// @returns A pointer to the data cast to a T*
  template<class T>
  T* array();
  /// @returns A const pointer to the data cast to a T const*
  template<class T>
  T const* array() const;
  /// @returns The size of the POD in T elements, AKA how many of type T could
  /// fit in the POD
  template<class T>
  size_t size_in() const;

  /// Output the POD to a stream
  friend std::ostream& operator<<(std::ostream& os, pod const& p)
  {
    for (size_t i = 0; i < p.size(); i++) { os << p[i]; }
    return os;
  }

private:
  void* m_data = nullptr;
  size_t m_size = 0;
};

template<class T>
pod::pod(T const* buffer, size_t size) :
    m_data(lkcpp::alloc<T>(size)), m_size(size)
{
  lkcpp::memcpy(m_data, static_cast<void const*>(buffer), sizeof(T) * size);
}

template<>
pod::pod(void const* buffer, size_t size);

template<class T>
inline T* pod::array()
{
  return static_cast<T*>(m_data);
}

template<class T>
inline T const* pod::array() const
{
  return static_cast<T const*>(m_data);
}

template<class T>
inline size_t pod::size_in() const
{
  return m_size / (float)sizeof(T);
}
} // namespace lkcpp