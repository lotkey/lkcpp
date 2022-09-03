#include "lkcpp/object.hpp"
#include "lkcpp/utility/pair.hpp"

#include "gtest/gtest.h"

TEST(test_pair, construct)
{
  lkcpp::pair<int, int> x;
  lkcpp::pair<int, int> y = x;
  EXPECT_EQ(x, y);
  lkcpp::pair<int, int> z = lkcpp::move(x);
  EXPECT_EQ(z, y);

  lkcpp::pair<int, int> const w(1, 2);
  EXPECT_EQ(1, w.first());
  EXPECT_EQ(2, w.second());
}

TEST(test_pair, assign)
{
  lkcpp::pair<int, double> x;
  lkcpp::pair<int, double> y;
  lkcpp::pair<int, double> z;
  x.first() = 1;
  x.second() = 1.5;

  y = x;
  EXPECT_EQ(x, y);
  z = lkcpp::move(x);
  EXPECT_EQ(z, y);
}

TEST(test_pair, modify)
{
  lkcpp::pair<int, int> x;
  x.first() = 1;
  x.second() = 2;
  EXPECT_EQ(1, x.first());
  EXPECT_EQ(2, x.second());
}