#include "lkcpp/memory/shared_ptr.hpp"
#include "lkcpp/memory/weak_ptr.hpp"
#include "lkcpp/object.hpp"

#include "gtest/gtest.h"

class Int {
public:
  Int() = default;
  Int(int i) : m_int(i) {}

  int value() const { return m_int; }
  bool operator==(Int const& other) const { return m_int == other.m_int; }
  bool operator!=(Int const& other) const { return m_int != other.m_int; }

private:
  int m_int = 0;
};

TEST(test_weak_ptr, construct)
{
  lkcpp::weak_ptr<int> p;
  EXPECT_FALSE(p);
  EXPECT_EQ(0, p.use_count());

  auto shared = lkcpp::shared_ptr<int>::make(10);
  lkcpp::weak_ptr<int> const p2 = shared;
  EXPECT_TRUE(p2);
  EXPECT_EQ(p2.get(), shared.get());
  EXPECT_EQ(p2.size(), shared.size());

  lkcpp::weak_ptr<int> const p3 = lkcpp::shared_ptr<int>::make(11);
  EXPECT_TRUE(p3);
  EXPECT_EQ(1, p3.size());
}

TEST(test_weak_ptr, assign)
{
  auto shared = lkcpp::shared_ptr<int>::make(10);
  lkcpp::weak_ptr<int> p;
  EXPECT_FALSE(p);
  p = shared;
  EXPECT_TRUE(p);
  EXPECT_TRUE(lkcpp::is(*p, *shared));
  EXPECT_EQ(1, p.use_count());
}

TEST(test_weak_ptr, deref)
{
  auto shared = lkcpp::shared_ptr<Int>::make(11);
  lkcpp::weak_ptr<Int> x = shared;
  lkcpp::weak_ptr<Int> const y = shared;
  EXPECT_EQ(*x, *y);
  EXPECT_EQ(11, x->value());
  EXPECT_EQ(11, y->value());
}

TEST(test_weak_ptr, lock)
{
  auto shared = lkcpp::shared_ptr<Int>::make(11);
  lkcpp::weak_ptr<Int> x = shared;
  auto shared2 = x.lock();
  EXPECT_EQ(shared, shared2);
}

TEST(test_weak_ptr, compare)
{
  auto shared1 = lkcpp::shared_ptr<Int>::make(11);
  auto shared2 = lkcpp::shared_ptr<Int>::make(12);

  lkcpp::weak_ptr<Int> x = shared1;
  lkcpp::weak_ptr<Int> y = shared1;
  lkcpp::weak_ptr<Int> z = shared2;

  EXPECT_EQ(x, y);
  EXPECT_NE(x, z);
}