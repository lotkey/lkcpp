#include "lkcpp/memory.hpp"

#include "gtest/gtest.h"

TEST(test_memory, memcpy1)
{
  char str[] = "abcdef";
  lkcpp::memcpy(str, str, 1000000000000);
  EXPECT_STREQ(str, str);
}

TEST(test_memory, memcpy2)
{
  char str[] = "abcdef123456";
  lkcpp::memcpy(str, str + 4, 6);
  EXPECT_STREQ("ef1234123456", str);
}

TEST(test_memory, memcpy3)
{
  char str[] = "abcdef123456";
  lkcpp::memcpy(str + 4, str, 6);
  EXPECT_STREQ("abcdabcdef56", str);
}

TEST(test_memory, memcpy4)
{
  char str1[] = "abcdef";
  char str2[] = "123456";
  lkcpp::memcpy(str1, str2, 6);
  EXPECT_STREQ(str1, str2);
}