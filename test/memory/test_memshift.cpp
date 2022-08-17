#include "lkcpp/memory/memcmp.hpp"
#include "lkcpp/memory/memshift.hpp"

#include "gtest/gtest.h"

TEST(test_memshift, base_case)
{
  int arr1[] = {1, 2, 3};
  lkcpp::memlshift(arr1, 3, 1);
  int expected1[] = {2, 3, 1};
  EXPECT_EQ(0, lkcpp::memcmp(arr1, expected1, 3));

  int arr2[] = {1, 2, 3};
  lkcpp::memrshift(arr2, 3, 1);
  int expected2[] = {3, 1, 2};
  EXPECT_EQ(0, lkcpp::memcmp(arr2, expected2, 3));
}

TEST(test_memshift, void_ptr)
{
  int arr1[] = {1, 2, 3};
  lkcpp::memlshift(static_cast<void*>(arr1), 3 * sizeof(int), sizeof(int));
  int expected1[] = {2, 3, 1};
  EXPECT_EQ(0, lkcpp::memcmp(arr1, expected1, 3));

  int arr2[] = {1, 2, 3};
  lkcpp::memrshift(static_cast<void*>(arr2), 3 * sizeof(int), sizeof(int));
  int expected2[] = {3, 1, 2};
  EXPECT_EQ(0, lkcpp::memcmp(arr2, expected2, 3));
}

TEST(test_memshift, char_ptr)
{
  char str1[] = "test";
  lkcpp::memlshift(str1, 4, 0);
  EXPECT_STREQ("test", str1);
  lkcpp::memlshift(str1, 0, 4);
  EXPECT_STREQ("test", str1);
  lkcpp::memrshift(str1, 4, 0);
  EXPECT_STREQ("test", str1);
  lkcpp::memrshift(str1, 0, 4);
  EXPECT_STREQ("test", str1);
}