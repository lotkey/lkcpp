#include "lkcpp/tuple.hpp"

#include "gtest/gtest.h"

TEST(test_tuple, test)
{
  lkcpp::tuple<int, int> x(1, 2);
  EXPECT_EQ(1, x.get<0>());
  EXPECT_EQ(2, x.get<1>());
  EXPECT_EQ(2, x.size());
}