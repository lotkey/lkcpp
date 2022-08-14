#include "lkcpp/memory.hpp"

#include "gtest/gtest.h"

TEST(test_unique_ptr, default_initialized)
{
  lkcpp::unique_ptr<int> p;
  EXPECT_FALSE(p.get());
  EXPECT_EQ(0, p.size());
}

TEST(test_unique_ptr, null_initialized)
{
  lkcpp::unique_ptr<int> p = nullptr;
  EXPECT_FALSE(p.get());
  EXPECT_EQ(0, p.size());
}

TEST(test_unique_ptr, single_initialized)
{
  lkcpp::unique_ptr<int> p = lkcpp::make_unique<int>(5);
  EXPECT_TRUE(p.get());
  EXPECT_EQ(5, *p);
  EXPECT_EQ(1, p.size());
}

TEST(test_unique_ptr, array_initialized)
{
  lkcpp::unique_ptr<int> p = lkcpp::make_unique_array<int>(5);
  EXPECT_TRUE(p.get());
  EXPECT_EQ(5, p.size());
}

TEST(test_unique_ptr, destructor)
{
  lkcpp::unique_ptr<int> p = lkcpp::make_unique<int>(5);
  EXPECT_TRUE(p.get());
  EXPECT_EQ(1, p.size());
  p.~unique_ptr<int>();
  EXPECT_TRUE(!p.get());
  EXPECT_EQ(0, p.size());
}

TEST(test_unique_ptr, logical)
{
  lkcpp::unique_ptr<int> p1 = (int*)1;
  lkcpp::unique_ptr<int> p2 = (int*)2;
  lkcpp::unique_ptr<int> p3 = nullptr;
  EXPECT_NE(p1, p2);
  EXPECT_EQ(p1, p1);
  EXPECT_LT(p1, p2);
  EXPECT_GT(p2, p1);
  EXPECT_LE(p1, p1);
  EXPECT_LE(p1, p2);
  EXPECT_GE(p1, p1);
  EXPECT_GE(p2, p1);
  p1.release();
  p2.release();
}

TEST(test_unique_ptr, array_setter)
{
  lkcpp::unique_ptr<int> arr = lkcpp::make_unique_array<int>(5);
  arr[4] = 3;
  EXPECT_EQ(3, arr[4]);
}

TEST(test_unique_ptr, swap)
{
  lkcpp::unique_ptr<int> p1 = (int*)1;
  lkcpp::unique_ptr<int> p2 = (int*)2;
  p1.swap(p2);
  EXPECT_EQ((int*)2, p1.get());
  EXPECT_EQ((int*)1, p2.get());
  p1.release();
  p2.release();
}