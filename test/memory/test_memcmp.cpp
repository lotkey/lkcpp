#include "lkcpp/memory/memcmp.hpp"

#include "gtest/gtest.h"

TEST(test_memcmp, base_case)
{
  int arr1[] = {1, 2, 3};
  int arr2[] = {1, 2, 3};
  EXPECT_EQ(0, lkcpp::memcmp(arr1, arr2, 3));
}

TEST(test_memcmp, void_ptr)
{
  int arr1[] = {1, 2, 3};
  int arr2[] = {1, 2, 3};
  EXPECT_EQ(
    0, lkcpp::memcmp(static_cast<void*>(arr1), static_cast<void*>(arr2), 3));
}

TEST(test_memcmp, char_ptr)
{
  char const str1[] = "abcd";
  char const str2[] = "abcd";
  char const str3[] = "abbd";
  EXPECT_EQ(0, lkcpp::memcmp(str1, str1, 5));
  EXPECT_EQ(0, lkcpp::memcmp(str1, str2, 5));
  EXPECT_EQ(1, lkcpp::memcmp(str1, str3, 5));
  EXPECT_EQ(-1, lkcpp::memcmp(str3, str1, 5));
}