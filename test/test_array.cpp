#include "lkcpp/array.hpp"
#include "lkcpp/assert.hpp"

#include "gtest/gtest.h"

TEST(test_array, logical_operators)
{
  lkcpp::array<int, 3> arr3;
  lkcpp::array<int, 4> arr4;

  for (size_t i = 0; i < 3; i++) { arr3[i] = i; }
  for (size_t i = 0; i < 4; i++) { arr4[i] = i; }

  EXPECT_EQ(arr3, arr3);
  EXPECT_NE(arr3, arr4);
  EXPECT_LT(arr3, arr4);
  EXPECT_GT(arr4, arr3);
  EXPECT_LE(arr3, arr4);
  EXPECT_GE(arr4, arr3);
  EXPECT_LE(arr3, arr3);
  EXPECT_GE(arr4, arr4);
}

TEST(test_array, fill)
{
  lkcpp::array<int, 4> arr;
  arr.fill(0);
  for (size_t i = 0; i < 4; i++) { EXPECT_EQ(0, arr[i]); }
}

TEST(test_array, setters)
{
  lkcpp::array<int, 4> arr;
  for (size_t i = 0; i < 4; i++) {
    arr[i] = i;
    EXPECT_EQ(i, arr[i]);
  }

  EXPECT_EQ(0, arr.front());
  EXPECT_EQ(3, arr.back());
}

TEST(test_array, out_of_bounds)
{
  lkcpp::array<int, 1> arr;
  EXPECT_THROW(arr[1], lkcpp::out_of_bounds_exception);
}