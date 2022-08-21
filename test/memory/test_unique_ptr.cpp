#include "lkcpp/memory/alloc.hpp"
#include "lkcpp/memory/unique_ptr.hpp"

#include "util/instance_counter.hpp"

#include "gtest/gtest.h"

#include <sstream>
#include <vector>

TEST(test_unique_ptr, default_construct)
{
  lkcpp::unique_ptr<instance_counter> p;
  EXPECT_EQ(nullptr, p.get());
  EXPECT_EQ(0, p.size());
  EXPECT_EQ(0, instance_counter::instance_count());
}

TEST(test_unique_ptr, nullptr_construct)
{
  lkcpp::unique_ptr<instance_counter> p = nullptr;
  EXPECT_EQ(nullptr, p.get());
  EXPECT_EQ(0, p.size());
  EXPECT_EQ(0, instance_counter::instance_count());
}

TEST(test_unique_ptr, move_construct)
{
  lkcpp::unique_ptr<instance_counter> p =
    lkcpp::unique_ptr<instance_counter>::make();
  EXPECT_EQ(1, instance_counter::instance_count());
  EXPECT_EQ(1, p.size());
  EXPECT_NE(nullptr, p.get());
}

TEST(test_unique_ptr, pointer_construct)
{
  auto* pointer = lkcpp::alloc_obj<instance_counter>();
  lkcpp::unique_ptr<instance_counter> p(pointer);
  EXPECT_EQ(1, p.size());
  EXPECT_EQ(pointer, p.get());
}

TEST(test_unique_ptr, dereference)
{
  auto p = lkcpp::unique_ptr<instance_counter>::make(10);
  EXPECT_EQ(instance_counter(10), *p);

  auto const& pref = p;
  EXPECT_EQ(instance_counter(10), *pref);
}

TEST(test_unique_ptr, arrow)
{
  auto p = lkcpp::unique_ptr<instance_counter>::make(10);
  EXPECT_EQ(10, p->value());

  auto const& pref = p;
  EXPECT_EQ(10, pref->value());
}

TEST(test_unique_ptr, index)
{
  auto p = lkcpp::unique_ptr<instance_counter>::make_array(5, 3);
  EXPECT_EQ(5, p.size());
  EXPECT_EQ(3, p[2].value());

  auto const& pref = p;
  EXPECT_EQ(3, pref[2].value());
}

TEST(test_unique_ptr, assignment)
{
  lkcpp::unique_ptr<instance_counter> p1;
  auto p2 = lkcpp::unique_ptr<instance_counter>::make(10);
  auto* ptr = p2.get();
  p1 = lkcpp::move(p2);
  EXPECT_EQ(ptr, p1.get());

  p1 = lkcpp::move(p1);
  EXPECT_EQ(ptr, p1.get());
}

TEST(test_unique_ptr, stream)
{
  std::stringstream ss1;
  lkcpp::unique_ptr<instance_counter> p1;
  ss1 << p1;
  EXPECT_STREQ(ss1.str().c_str(), "0");

  std::stringstream ss2;
  p1 = lkcpp::unique_ptr<instance_counter>::make(10);
  ss2 << p1;
  EXPECT_EQ('0', ss2.str()[0]);
  EXPECT_EQ('x', ss2.str()[1]);
}

TEST(test_unique_ptr, reset)
{
  auto p = lkcpp::unique_ptr<instance_counter>::make(10);
  EXPECT_EQ(1, instance_counter::instance_count());
  p.reset();
  EXPECT_EQ(0, instance_counter::instance_count());
  p.reset(lkcpp::alloc_obj<instance_counter>(10));
  EXPECT_EQ(1, instance_counter::instance_count());
}

TEST(test_unique_ptr, compare)
{
  auto p1 = lkcpp::unique_ptr<instance_counter>::make(10);
  auto p2 = lkcpp::unique_ptr<instance_counter>::make(10);
  EXPECT_NE(p1, p2);
  EXPECT_EQ(p1, p1);
}

TEST(test_unique_ptr, swap)
{
  auto p1 = lkcpp::unique_ptr<instance_counter>::make(10);
  auto* ptr1 = p1.get();
  auto size1 = p1.size();
  auto p2 = lkcpp::unique_ptr<instance_counter>::make_array(10, 2);
  auto* ptr2 = p2.get();
  auto size2 = p2.size();

  lkcpp::swap(p1, p2);
  EXPECT_EQ(ptr1, p2.get());
  EXPECT_EQ(size1, p2.size());
  EXPECT_EQ(ptr2, p1.get());
  EXPECT_EQ(size2, p1.size());
}

TEST(test_unique_ptr, test)
{
  std::vector<lkcpp::unique_ptr<instance_counter>> v;
  auto p = lkcpp::unique_ptr<instance_counter>::make();
  auto ptr = p.get();
  EXPECT_EQ(1, p.size());

  v.push_back(lkcpp::move(p));
  EXPECT_EQ(0, p.size());
  EXPECT_EQ(nullptr, p.get());

  EXPECT_EQ(1, instance_counter::instance_count());
  EXPECT_EQ(1, v.back().size());
  EXPECT_EQ(ptr, v.back().get());

  v.clear();
  EXPECT_EQ(0, instance_counter::instance_count());
}