#pragma once

#include "lkcpp/pod.hpp"

namespace lkcpp {
class pod_view {
public:
  pod_view() = default;
  pod_view(pod& p, size_t offset = 0);
  pod_view(pod& p, size_t offset, size_t size);
  pod_view(pod_view const& other) = default;
  pod_view(pod_view&& other) = default;
  pod_view& operator=(pod_view const& other) = default;
  pod_view& operator=(pod_view&& other) = default;
  virtual ~pod_view();

  void clear();
  void swap(pod_view& other);
  void resize(size_t size);
  pod_view& operator+=(size_t offset);
  pod_view& operator-=(size_t offset);
  bool operator==(pod_view const& other) const;
  bool operator!=(pod_view const& other) const;

  bool null() const;
  operator bool() const;
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

  pod_view& operator>>(int num_shifts);
  pod_view& operator<<(int num_shifts);

  template<class T>
  T* array();
  template<class T>
  T const* array() const;
  template<class T>
  size_t size_in() const;

  friend std::ostream& operator<<(std::ostream& os, pod_view const& pv)
  {
    for (size_t i = 0; i < pv.size(); i++) { os << pv[i]; }
    return os;
  }

private:
  pod* m_pod = nullptr;
  size_t m_offset = 0;
  size_t m_size = 0;
};

template<class T>
inline T* pod_view::array()
{
  if (null()) { return nullptr; }
  return static_cast<T*>(static_cast<void*>(m_pod->bytes() + m_offset));
}

template<class T>
inline T const* pod_view::array() const
{
  if (null()) { return nullptr; }
  return static_cast<T const*>(
    static_cast<void const*>(m_pod->bytes() + m_offset));
}

template<class T>
inline size_t pod_view::size_in() const
{
  return m_size / (float)sizeof(T);
}
} // namespace lkcpp