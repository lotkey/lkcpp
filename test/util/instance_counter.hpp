#pragma once

#include "lkcpp/def.hpp"

#include <vector>

class instance_counter {
public:
  static lkcpp::size_t instance_count() { return s_instance_count; }
  static void reset() { s_instance_count = 0; }

  instance_counter(int value = 0) : m_value(value) { s_instance_count++; }
  instance_counter(instance_counter const& other) : m_value(other.m_value)
  {
    s_instance_count++;
  }
  instance_counter(instance_counter&& other) : m_value(other.m_value)
  {
    s_instance_count++;
  }
  instance_counter& operator=(instance_counter const&) = default;
  instance_counter& operator=(instance_counter&&) = default;
  virtual ~instance_counter() { s_instance_count--; }

  bool operator==(instance_counter const& other) const
  {
    return m_value == other.m_value;
  }
  bool operator!=(instance_counter const& other) const
  {
    return !(*this == other);
  }

  int value() const { return m_value; }

private:
  static lkcpp::size_t s_instance_count;

  int m_value;
};