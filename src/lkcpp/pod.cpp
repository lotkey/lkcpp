#include "lkcpp/pod.hpp"
#include "lkcpp/memory.hpp"
#include "lkcpp/object.hpp"
#include "lkcpp/utility.hpp"

namespace lkcpp {
pod::pod(size_t size) : m_data(lkcpp::alloc<void>(size)), m_size(size)
{
  lkcpp::memfill(m_data, '\0', size);
}

template<>
pod::pod(void const* buffer, size_t size) :
    pod(static_cast<char const*>(buffer), size)
{}

pod::pod(pod const& other) : pod(other.bytes(), other.m_size) {}

pod::pod(pod&& other) : m_data(other.m_data), m_size(other.m_size)
{
  other.m_data = nullptr;
  other.m_size = 0;
}

pod& pod::operator=(pod const& other)
{
  clear();
  m_data = lkcpp::alloc<void>(other.m_size);
  m_size = other.m_size;
  lkcpp::memcpy(m_data, other.data(), other.size());
  return *this;
}

pod& pod::operator=(pod&& other)
{
  clear();
  m_data = other.m_data;
  m_size = other.m_size;
  other.m_data = nullptr;
  other.m_size = 0;
  return *this;
}

pod::~pod() { clear(); }

void pod::clear()
{
  if (m_data) {
    lkcpp::dealloc(m_data);
    m_data = nullptr;
    m_size = 0;
  }
}

void pod::swap(pod& other)
{
  lkcpp::swap(m_data, other.m_data);
  lkcpp::swap(m_size, other.m_size);
}

void pod::resize(size_t size)
{
  size_t tmp_size = m_size;
  m_data = lkcpp::realloc<void>(m_data, size);
  m_size = size;

  if (size > tmp_size) {
    size_t zero_start = tmp_size;
    size_t zero_len = size - tmp_size;
    lkcpp::memfill(static_cast<char*>(m_data) + zero_start, '\0', zero_len);
  }
}

bool pod::operator==(pod const& other) const
{
  if (other.size() != m_size) { return false; }

  for (size_t i = 0; i < m_size; i++) {
    if (bytes()[i] != other.bytes()[i]) { return false; }
  }
  return true;
}

bool pod::operator!=(pod const& other) const { return !(*this == other); }

size_t pod::size() const { return m_size; }

bool pod::empty() const { return m_size == 0; }

void* pod::data() { return m_data; }

void const* pod::data() const { return m_data; }

char* pod::bytes() { return static_cast<char*>(m_data); }

char const* pod::bytes() const { return static_cast<char const*>(m_data); }

char& pod::at(size_t index) { return bytes()[index]; }

char pod::at(size_t index) const { return bytes()[index]; }

char& pod::operator[](size_t index) { return at(index); }

char pod::operator[](size_t index) const { return at(index); }

char& pod::front() { return at(0); }

char pod::front() const { return at(0); }

char& pod::back() { return at(size() - 1); }

char pod::back() const { return at(size() - 1); }

pod& pod::operator>>(size_t num_shifts)
{
  if (size() == 0) { return *this; }
  char* data = lkcpp::alloc<char>(m_size);
  lkcpp::memcpy(data + num_shifts, bytes(), m_size - num_shifts);
  lkcpp::memcpy(data, bytes() + (m_size - num_shifts), num_shifts);
  lkcpp::dealloc(m_data);
  m_data = data;
  return *this;
}

pod& pod::operator<<(size_t num_shifts)
{
  if (size() == 0) { return *this; }
  char* data = lkcpp::alloc<char>(m_size);
  lkcpp::memcpy(data + (m_size - num_shifts), bytes(), num_shifts);
  lkcpp::memcpy(data, bytes() + num_shifts, m_size - num_shifts);
  lkcpp::dealloc(m_data);
  m_data = data;
  return *this;
}
} // namespace lkcpp