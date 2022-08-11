#pragma once

#include <iostream>
#include <stdexcept>

#define ASSERT(condition)                                                      \
  {                                                                            \
    if (!(condition)) {                                                        \
      std::cerr << "Assert failed: " << #condition << std::endl;               \
      std::cerr << (condition) << " != true" << std::endl;                     \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
#define ASSERT_EQ(expected_value, value)                                       \
  {                                                                            \
    if (expected_value != value) {                                             \
      std::cerr << "Assert failed: " << #expected_value << " == " << #value    \
                << std::endl;                                                  \
      std::cerr << (expected_value) << " != " << (value) << std::endl;         \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
#define ASSERT_NE(expected_value, value)                                       \
  {                                                                            \
    if (expected_value == value) {                                             \
      std::cerr << "Assert failed: " << #expected_value << " != " << #value    \
                << std::endl;                                                  \
      std::cerr << (expected_value) << " == " << (value) << std::endl;         \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
#define ASSERT_LT(expected_value, value)                                       \
  {                                                                            \
    if (expected_value >= value) {                                             \
      std::cerr << "Assert failed: " << #expected_value << " < " << #value     \
                << std::endl;                                                  \
      std::cerr << (expected_value) << " >= " << (value) << std::endl;         \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
#define ASSERT_GT(expected_value, value)                                       \
  {                                                                            \
    if (expected_value <= value) {                                             \
      std::cerr << "Assert failed: " << #expected_value << " > " << #value     \
                << std::endl;                                                  \
      std::cerr << (expected_value) << " <= " << (value) << std::endl;         \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
#define ASSERT_LE(expected_value, value)                                       \
  {                                                                            \
    if (expected_value > value) {                                              \
      std::cerr << "Assert failed: " << #expected_value << " <= " << #value    \
                << std::endl;                                                  \
      std::cerr << (expected_value) << " > " << (value) << std::endl;          \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }
#define ASSERT_GE(expected_value, value)                                       \
  {                                                                            \
    if (expected_value < value) {                                              \
      std::cerr << "Assert failed: " << #expected_value << " >= " << #value    \
                << std::endl;                                                  \
      std::cerr << (expected_value) << " < " << (value) << std::endl;          \
      throw std::runtime_error("Assert failed.");                              \
    }                                                                          \
  }

// Comment to avoid "backslash-newline at end of file" warning