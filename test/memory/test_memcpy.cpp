#include "lkcpp/memory/memcmp.hpp"
#include "lkcpp/memory/memcpy.hpp"

#include "gtest/gtest.h"

TEST(test_memcpy, base_case)
{
  int arr1[] = {1, 2, 3};
  int arr2[] = {0, 0, 0};
  lkcpp::memcpy(arr2, arr1, 3);
  EXPECT_EQ(0, lkcpp::memcmp(arr1, arr2, 3));
}

TEST(test_memcpy, void_ptr)
{
  int arr1[] = {1, 2, 3};
  int arr2[] = {0, 0, 0};
  lkcpp::memcpy(
    static_cast<void*>(arr2), static_cast<void*>(arr1), 3 * sizeof(int));
  EXPECT_EQ(0, lkcpp::memcmp(arr1, arr2, 3));
}

TEST(test_memcpy, char_ptr)
{
  char str1[] = "test";
  char str2[] = "    ";
  lkcpp::memcpy(str2, str1, 5);
  EXPECT_STREQ(str1, str2);

  lkcpp::memcpy(str1, str1, 5);
  EXPECT_STREQ(str1, str1);

  char str3[] = "abcd";
  lkcpp::memcpy(str3 + 1, str3, 2);
  EXPECT_STREQ("aabd", str3);

  char str4[] = "abcd";
  lkcpp::memcpy(str4, str4 + 1, 2);
  EXPECT_STREQ("bccd", str4);
}