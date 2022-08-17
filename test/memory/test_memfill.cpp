#include "lkcpp/memory/memcmp.hpp"
#include "lkcpp/memory/memfill.hpp"

#include "gtest/gtest.h"

TEST(test_memfill, base_case)
{
  int arr[] = {1, 2, 3};
  lkcpp::memfill(arr, 0, 3);
  int arr_expected[] = {0, 0, 0};
  EXPECT_EQ(0, lkcpp::memcmp(arr_expected, arr, 3));
}

TEST(test_memfill, void_ptr)
{
  char str[] = "test";
  lkcpp::memfill(static_cast<void*>(str), ' ', 4);
  char str_expected[] = "    ";
  EXPECT_STREQ(str_expected, str);
}