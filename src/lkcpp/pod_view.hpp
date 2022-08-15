////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/pod.hpp"

namespace lkcpp {
/// Non-owning view into a lkcpp::pod's contents
class pod_view {
public:
  pod_view() = default;
  pod_view& operator=(pod_view const& other) = default;
  pod_view& operator=(pod_view&& other) = default;
  pod_view(pod_view const& other) = default;
  pod_view(pod_view&& other) = default;
  virtual ~pod_view() = default;

  /// Construct from a pod
  /// @param p pod to view
  /// @param offset Offset to start view at
  pod_view(pod& p, size_t offset = 0);
  /// Construct from a pod
  /// @param p pod to view
  /// @param offset Offset to start view at
  /// @param size Length of view
  pod_view(pod& p, size_t offset, size_t size);

  /// Clear the view
  void clear();
  /// Swap views with another pod_view
  void swap(pod_view& other);
  /// Change the length of the view
  void resize(size_t size);
  /// If possible, shift the view up in memory to view the upper portion of a
  /// pod
  pod_view& operator+=(size_t offset);
  /// If possible, shift the view down in memory to view the lower portion of a
  /// PDO
  pod_view& operator-=(size_t offset);
  /// @returns True if all the elements in the two pod_views are identical
  bool operator==(pod_view const& other) const;
  /// @returns False if all the elements in the two pod_views are identical
  bool operator!=(pod_view const& other) const;

  /// @returns True if not pod is being viewed
  bool null() const;
  /// @returns True if a pod is being viewed
  operator bool() const;
  /// @returns The size of the view (bytes)
  size_t size() const;
  /// @returns True if the size of the view is 0
  bool empty() const;
  /// @returns A pointer to the first byte begin viewed
  void* data();
  /// @returns A const pointer to the first byte begin viewed
  void const* data() const;
  /// @returns A char pointer to the first byte begin viewed
  char* bytes();
  /// @returns A const char pointer to the first byte begin viewed
  char const* bytes() const;
  /// @returns A reference to the index-th element in the pod_view
  char& at(size_t index);
  /// @returns A copy of the index-th element in the pod_view
  char at(size_t index) const;
  /// @returns A reference to the index-th element in the pod_view
  char& operator[](size_t index);
  /// @returns A copy of the index-th element in the pod_view
  char operator[](size_t index) const;
  /// @returns A reference to the first byte being viewed
  char& front();
  /// @returns A copy of the first byte being viewed
  char front() const;
  /// @returns A reference to the last byte being viewed
  char& back();
  /// @returns A copy of the last byte being viewed
  char back() const;

  /// Shift the entire view to the right, wrapping around to the front
  pod_view& operator>>(int num_shifts);
  /// Shift the entire view to the left, wrapping around to the back
  pod_view& operator<<(int num_shifts);

  /// @returns A pointer to the data cast to a T*
  template<class T>
  T* array();
  /// @returns A pointer to the data cast to a T const*
  template<class T>
  T const* array() const;
  /// @returns The size of the view in T elements, AKA how many of type T
  /// could fit in the view
  template<class T>
  size_t size_in() const;

  /// Output the pod_view to a stream
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