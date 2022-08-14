////////////////////////////////////////////////////////////////////////////////
/// Macros for assert statements
/// Modeled after gtest asserts
///
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <stdexcept>

// Asserts that some condition is true
#define ASSERT(condition)                                                      \
  {                                                                            \
    if (!(condition)) {                                                        \
      std::cerr << "Assert failed: " << #condition << "." << std::endl;        \
      std::cerr << (condition) << " is actually not true." << std::endl;       \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
/// Asserts that x == y
/// @param expected_value The expected value of value
/// @param value The value to test equality with the expected value
#define ASSERT_EQ(expected_value, value)                                       \
  {                                                                            \
    if ((expected_value) != (value)) {                                         \
      std::cerr << "Assert failed: " << #expected_value << " == " << #value    \
                << "." << std::endl;                                           \
      std::cerr << (expected_value) << " is actually not equal to " << (value) \
                << "." << std::endl;                                           \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
/// Asserts that x != y
#define ASSERT_NE(x, y)                                                        \
  {                                                                            \
    if ((x) == (y)) {                                                          \
      std::cerr << "Assert failed: " << #x << " != " << #y << std::endl;       \
      std::cerr << (x) << " is actually equal to " << (y) << std::endl;        \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
/// Asserts that x < y
#define ASSERT_LT(x, y)                                                        \
  {                                                                            \
    if ((x) >= (y)) {                                                          \
      std::cerr << "Assert failed: " << #x << " < " << #y << "." << std::endl; \
      std::cerr << (x) << " is actually not less than " << (y) << "."          \
                << std::endl;                                                  \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
/// Asserts that x > y
#define ASSERT_GT(x, y)                                                        \
  {                                                                            \
    if ((x) <= (y)) {                                                          \
      std::cerr << "Assert failed: " << #x << " > " << #y << "." << std::endl; \
      std::cerr << (x) << " is actually not greater than " << (y) << "."       \
                << std::endl;                                                  \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
/// Asserts that x <= y
#define ASSERT_LE(x, y)                                                        \
  {                                                                            \
    if ((x) > (y)) {                                                           \
      std::cerr << "Assert failed: " << #x << " <= " << #y << "."              \
                << std::endl;                                                  \
      std::cerr << (x) << " is actually greater than " << (y) << "."           \
                << std::endl;                                                  \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
/// Asserts that x >= y
#define ASSERT_GE(x, y)                                                        \
  {                                                                            \
    if (x < y) {                                                               \
      std::cerr << "Assert failed: " << #x << " >= " << #y << "."              \
                << std::endl;                                                  \
      std::cerr << (x) << " is actually less than " << (y) << "."              \
                << std::endl;                                                  \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }

// Comment to avoid "backslash-newline at end of file" warning