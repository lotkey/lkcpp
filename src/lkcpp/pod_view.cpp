#include "lkcpp/pod_view.hpp"
#include "lkcpp/algorithm.hpp"
#include "lkcpp/assert.hpp"
#include "lkcpp/except.hpp"
#include "lkcpp/memory.hpp"
#include "lkcpp/utility.hpp"

namespace lkcpp {
pod_view::pod_view(pod& p, size_t offset) :
    m_pod(&p), m_offset(offset), m_size(p.size() - offset)
{}

pod_view::pod_view(pod& p, size_t offset, size_t size) :
    m_pod(&p), m_offset(offset), m_size(size)
{
  ASSERT_GT(p.size(), offset + size);
}

void pod_view::clear() { m_pod = nullptr; }

void pod_view::swap(pod_view& other)
{
  lkcpp::swap(m_pod, other.m_pod);
  lkcpp::swap(m_offset, other.m_offset);
}

void pod_view::resize(size_t size)
{
  if (null()) { return; }

  if (size + m_offset > m_pod->size()) {
    throw out_of_bounds_exception(size, 0, m_pod->size() - m_offset);
  }
  m_size = size;
}

pod_view& pod_view::operator+=(size_t offset)
{
  if (offset >= size()) {
    throw out_of_bounds_exception(offset, 0, size() - 1);
  }
  m_offset += offset;
  m_size -= offset;
  return *this;
}

pod_view& pod_view::operator-=(size_t offset)
{
  if (offset > m_offset) { throw out_of_bounds_exception(offset, 0, m_offset); }
  m_offset -= offset;
  m_size += offset;
  return *this;
}

bool pod_view::operator==(pod_view const& other) const
{
  if (size() != other.size()) { return false; }
  return lkcpp::equal(bytes(), bytes() + m_size, other.bytes());
}

bool pod_view::operator!=(pod_view const& other) const
{
  return !(*this == other);
}

bool pod_view::null() const { return m_pod == nullptr; }

pod_view::operator bool() const { return !null(); }

size_t pod_view::size() const { return m_size; }

bool pod_view::empty() const { return m_size == 0; }

void* pod_view::data()
{
  if (null()) { return nullptr; }
  return m_pod->bytes() + m_offset;
}

void const* pod_view::data() const
{
  if (null()) { return nullptr; }
  return m_pod->bytes() + m_offset;
}

char* pod_view::bytes()
{
  if (null()) { return nullptr; }
  return m_pod->bytes() + m_offset;
}

char const* pod_view::bytes() const
{
  if (null()) { return nullptr; }
  return m_pod->bytes() + m_offset;
}

char& pod_view::at(size_t index) { return m_pod->at(index + m_offset); }

char pod_view::at(size_t index) const { return m_pod->at(index + m_offset); }

char& pod_view::operator[](size_t index) { return at(index); }

char pod_view::operator[](size_t index) const { return at(index); }

char& pod_view::front() { return at(0); }

char pod_view::front() const { return at(0); }

char& pod_view::back() { return at(m_size - 1); }

char pod_view::back() const { return at(m_size - 1); }

pod_view& pod_view::operator>>(int num_shifts)
{
  if (size() == 0) { return *this; }
  num_shifts %= size();
  char* data = static_cast<char*>(lkcpp::alloc<void>(size()));
  lkcpp::memcpy(data + num_shifts, bytes(), size() - num_shifts);
  lkcpp::memcpy(data, bytes() + (size() - num_shifts), num_shifts);
  lkcpp::memcpy(bytes(), data, size());
  lkcpp::dealloc(data);
  return *this;
}

pod_view& pod_view::operator<<(int num_shifts)
{
  if (size() == 0) { return *this; }
  num_shifts %= size();
  char* data = lkcpp::alloc<char>(size());
  lkcpp::memcpy(data + (size() - num_shifts), bytes(), num_shifts);
  lkcpp::memcpy(data, bytes() + num_shifts, size() - num_shifts);
  lkcpp::memcpy(bytes(), data, size());
  lkcpp::dealloc(data);
  return *this;
}
} // namespace lkcpp