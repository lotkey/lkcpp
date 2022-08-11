#include "lkcpp/vector.hpp"

#include "gtest/gtest.h"

TEST(test_vector, default_initialize)
{
  lkcpp::vector<int> v;
  EXPECT_EQ(0, v.size());
}

TEST(test_vector, reserve_initialize)
{
  lkcpp::vector<int> w(5);
  EXPECT_EQ(0, w.size());
}

TEST(test_vector, modify)
{
  lkcpp::vector<int> v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
    EXPECT_EQ(i, v.back());
    EXPECT_EQ(v[i], v.back());
    EXPECT_EQ(i + 1, v.size());
    v.back() = 0;
    EXPECT_EQ(0, v.back());
  }

  while (!v.empty()) {
    size_t size = v.size();
    v.pop_back();
    EXPECT_EQ(size - 1, v.size());
  }
  EXPECT_TRUE(v.empty());
}

TEST(test_vector, out_of_bounds)
{
  lkcpp::vector<int> x(1);
  EXPECT_THROW(x[0], lkcpp::out_of_bounds_exception);
}