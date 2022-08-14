#include "lkcpp/algorithm.hpp"
#include "lkcpp/pod.hpp"

#include "gtest/gtest.h"

#include <sstream>

TEST(test_pod, default_initialized)
{
  lkcpp::pod p;
  EXPECT_EQ(nullptr, p.bytes());
}

TEST(test_pod, size_initialized)
{
  lkcpp::pod p(1);
  EXPECT_EQ(1, p.size());
  EXPECT_EQ(0, p.bytes()[0]);
}

TEST(test_pod, clear)
{
  lkcpp::pod p(10);
  p.clear();
}

TEST(test_pod, shift)
{
  {
    lkcpp::pod p(10);
    for (size_t i = 0; i < 10; i++) { p[i] = '0' + i; }
    p << 2;
    std::stringstream ss;
    ss << p;
    EXPECT_STREQ("2345678901", ss.str().c_str());
  }
  {
    lkcpp::pod p(10);
    for (size_t i = 0; i < 10; i++) { p[i] = '0' + i; }
    p >> 2;
    std::stringstream ss;
    ss << p;
    EXPECT_STREQ("8901234567", ss.str().c_str());
  }
}

TEST(test_pod, resize1)
{
  lkcpp::pod p(1);
  p.bytes()[0] = 1;
  p.resize(2);
  EXPECT_EQ(2, p.size());
  EXPECT_EQ(1, p.bytes()[0]);
  EXPECT_EQ(0, p.bytes()[1]);
  p.resize(1);
  EXPECT_EQ(1, p.size());
  EXPECT_EQ(1, p.bytes()[0]);
}

TEST(test_pod, resize2)
{
  lkcpp::pod p(10);
  for (size_t i = 0; i < 10; i++) { p[i] = 'a' + i; }
  p.resize(15);
  char const expected[] = "abcdefghij\0\0\0\0";

  EXPECT_TRUE(lkcpp::equal(expected, expected + 15, p.bytes()));

  p.resize(5);
  EXPECT_TRUE(lkcpp::equal(expected, expected + 5, p.bytes()));
}
