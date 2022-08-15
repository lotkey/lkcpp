#pragma once

#include "lkcpp/def.hpp"
#include "lkcpp/memory.hpp"

#include <iostream>

namespace lkcpp {
class pod {
public:
  pod() = default;

  pod(size_t size);
  template<class T>
  pod(T const* buffer, size_t size);
  pod(pod const& other);
  pod(pod&& other);
  pod& operator=(pod const& other);
  pod& operator=(pod&& other);
  virtual ~pod();

  void clear();
  void swap(pod& other);
  void resize(size_t size);
  bool operator==(pod const& other) const;
  bool operator!=(pod const& other) const;

  size_t size() const;
  bool empty() const;
  void* data();
  void const* data() const;
  char* bytes();
  char const* bytes() const;
  char& at(size_t index);
  char at(size_t index) const;
  char& operator[](size_t index);
  char operator[](size_t index) const;
  char& front();
  char front() const;
  char& back();
  char back() const;

  pod& operator>>(size_t num_shifts);
  pod& operator<<(size_t num_shifts);

  template<class T>
  T* array();
  template<class T>
  T const* array() const;
  template<class T>
  size_t size_in() const;

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