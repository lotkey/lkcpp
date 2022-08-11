#include "lkcpp/dynamic_array.hpp"

#include "gtest/gtest.h"

TEST(test_dynamic_array, init_size)
{
  lkcpp::dynamic_array<int> arr(5);
  EXPECT_EQ(5, arr.size());
}

TEST(test_dynamic_array, copy_construct)
{
  lkcpp::dynamic_array<int> a1(5);
  lkcpp::dynamic_array<int> a2(a1);
  EXPECT_EQ(a1, a2);
}

TEST(test_dynamic_array, logical_operators)
{
  lkcpp::dynamic_array<int> x(3);
  lkcpp::dynamic_array<int> y(4);

  for (size_t i = 0; i < x.size(); i++) { x[i] = i; }
  for (size_t i = 0; i < y.size(); i++) { y[i] = i; }

  EXPECT_EQ(x, x);
  EXPECT_NE(x, y);
  EXPECT_LT(x, y);
  EXPECT_GT(y, x);
  EXPECT_LE(x, y);
  EXPECT_GE(y, x);
  EXPECT_LE(x, x);
  EXPECT_GE(y, y);
}

TEST(test_dynamic_array, fill)
{
  lkcpp::dynamic_array<int> arr(4);
  arr.fill(0);
  for (size_t i = 0; i < arr.size(); i++) { EXPECT_EQ(0, arr[i]); }
}

TEST(test_dynamic_array, setters)
{
  lkcpp::dynamic_array<int> arr(5);
  for (size_t i = 0; i < arr.size(); i++) {
    arr[i] = i;
    EXPECT_EQ(i, arr[i]);
  }

  EXPECT_EQ(0, arr.front());
  EXPECT_EQ(arr.size() - 1, arr.back());
}

TEST(test_dynamic_array, resizing)
{
  lkcpp::dynamic_array<int> x(5);
  x.fill(0);
  lkcpp::dynamic_array<int> y = x;
  y.resize(2);
  EXPECT_EQ(2, y.size());
  EXPECT_NE(x, y);
  EXPECT_GE(x, y);
}

TEST(test_dynamic_array, out_of_bounds)
{
  lkcpp::dynamic_array<int> x(1);
  EXPECT_THROW(x[1], lkcpp::out_of_bounds_exception);
}