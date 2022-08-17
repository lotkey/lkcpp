#include "lkcpp/def.hpp"
#include "lkcpp/memory/alloc.hpp"

#include "gtest/gtest.h"

#include <vector>

class test {
public:
  static lkcpp::size_t instance_count() { return s_instance_count; }
  static void reset()
  {
    for (auto p : s_instances) { p->~test(); }
  }

  test()
  {
    s_instance_count++;
    s_instances.push_back(this);
  }
  test(test const&)
  {
    s_instance_count++;
    s_instances.push_back(this);
  }
  test(test&&)
  {
    s_instance_count++;
    s_instances.push_back(this);
  }
  test& operator=(test const&) = default;
  test& operator=(test&&) = default;
  ~test()
  {
    s_instance_count--;
    auto it = std::find(s_instances.begin(), s_instances.end(), this);
    if (it != s_instances.end()) { s_instances.erase(it); }
  }

private:
  static lkcpp::size_t s_instance_count;
  static std::vector<test*> s_instances;
};
lkcpp::size_t test::s_instance_count = 0;
std::vector<test*> test::s_instances = {};

TEST(test_alloc, alloc_base_case)
{
  test* arr = lkcpp::alloc<test>(10);
  EXPECT_EQ(0, test::instance_count());
  lkcpp::dealloc(arr);
}

TEST(test_alloc, alloc_obj)
{
  test* obj = lkcpp::alloc_obj<test>();
  EXPECT_EQ(1, test::instance_count());
  lkcpp::dealloc_objs(obj);
  EXPECT_EQ(0, test::instance_count());
}

TEST(test_alloc, alloc_objs)
{
  test* objs = lkcpp::alloc_objs<test>(10);
  EXPECT_EQ(10, test::instance_count());
  lkcpp::dealloc_objs(objs);
  EXPECT_EQ(0, test::instance_count());
}

TEST(test_alloc, realloc)
{
  test* objs = lkcpp::alloc_objs<test>(10);
  objs = lkcpp::realloc(objs, 2);
  EXPECT_EQ(10, test::instance_count());
  lkcpp::dealloc(objs);
  test::reset();
}

TEST(test_alloc, realloc_objs1)
{
  test* objs = lkcpp::alloc_objs<test>(10);
  objs = lkcpp::realloc_objs(objs, 2);
  EXPECT_EQ(2, test::instance_count());
  lkcpp::dealloc_objs(objs);
}

TEST(test_alloc, realloc_objs2)
{
  test* objs = lkcpp::alloc_objs<test>(10);
  objs = lkcpp::realloc_objs(objs, 11);
  EXPECT_EQ(11, test::instance_count());
  lkcpp::dealloc_objs(objs);
}

TEST(test_alloc, realloc_objs_nullptr)
{
  test* objs = lkcpp::realloc_objs<test>(nullptr, 10);
  EXPECT_EQ(10, test::instance_count());
  lkcpp::dealloc_objs(objs);
}

TEST(test_alloc, dealloc_nullptr)
{
  test* p = nullptr;
  EXPECT_NO_FATAL_FAILURE(lkcpp::dealloc(p));
  EXPECT_NO_FATAL_FAILURE(lkcpp::dealloc_objs(p));
}

class big_object {
private:
  int m_arr[10000000];
};

TEST(test_alloc, alloc_exception)
{
  std::vector<big_object*> ptrs;
  auto keep_allocing = [&ptrs]() {
    while (true) { ptrs.push_back(lkcpp::alloc<big_object>(100000)); }
  };
  EXPECT_THROW(keep_allocing(), lkcpp::failed_allocation_exception);
  for (auto p : ptrs) { lkcpp::dealloc(p); }
}

TEST(test_alloc, realloc_exception)
{
  big_object* p = lkcpp::alloc<big_object>(1);
  lkcpp::size_t size = 1;
  auto keep_reallocing = [&p, &size]() {
    while (true) {
      p = lkcpp::realloc(p, size + 1000);
      size += 1000;
    }
  };
  EXPECT_THROW(keep_reallocing(), lkcpp::failed_allocation_exception);
}