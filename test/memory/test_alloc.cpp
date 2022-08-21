#include "util/big_object.hpp"
#include "util/instance_counter.hpp"

#include "lkcpp/def.hpp"
#include "lkcpp/memory/alloc.hpp"

#include "gtest/gtest.h"

#include <iostream>
#include <vector>

TEST(test_alloc, alloc_base_case)
{
  instance_counter* arr = lkcpp::alloc<instance_counter>(10);
  EXPECT_EQ(0, instance_counter::instance_count());
  lkcpp::dealloc(arr);
}

TEST(test_alloc, alloc_obj)
{
  instance_counter* obj = lkcpp::alloc_obj<instance_counter>();
  EXPECT_EQ(1, instance_counter::instance_count());
  lkcpp::dealloc_objs(obj, 1);
  EXPECT_EQ(0, instance_counter::instance_count());
}

TEST(test_alloc, alloc_objs)
{
  instance_counter* objs = lkcpp::alloc_objs<instance_counter>(10);
  EXPECT_EQ(10, instance_counter::instance_count());
  lkcpp::dealloc_objs(objs, 10);
  EXPECT_EQ(0, instance_counter::instance_count());
}

TEST(test_alloc, realloc)
{
  instance_counter* objs = lkcpp::alloc_objs<instance_counter>(10);
  objs = lkcpp::realloc(objs, 2);
  EXPECT_EQ(10, instance_counter::instance_count());
  lkcpp::dealloc(objs);
  instance_counter::reset();
}

TEST(test_alloc, realloc_objs1)
{
  instance_counter* objs = lkcpp::alloc_objs<instance_counter>(10);
  objs = lkcpp::realloc_objs(objs, 10, 2);
  EXPECT_EQ(2, instance_counter::instance_count());
  lkcpp::dealloc_objs(objs, 2);
}

TEST(test_alloc, realloc_objs2)
{
  instance_counter* objs = lkcpp::alloc_objs<instance_counter>(10);
  objs = lkcpp::realloc_objs(objs, 10, 11);
  EXPECT_EQ(11, instance_counter::instance_count());
  lkcpp::dealloc_objs(objs, 11);
}

TEST(test_alloc, realloc_objs3)
{
  instance_counter* p = nullptr;
  p = lkcpp::realloc_objs(p, 0, 10);
  EXPECT_EQ(10, instance_counter::instance_count());
  lkcpp::dealloc_objs(p, 10);
}

TEST(test_alloc, realloc_objs4)
{
  instance_counter* p = lkcpp::alloc_objs<instance_counter>(10);
  p = lkcpp::realloc_objs(p, 10, 0);
  EXPECT_EQ(0, instance_counter::instance_count());
  EXPECT_EQ(nullptr, p);
}

TEST(test_alloc, realloc_objs_nullptr)
{
  instance_counter* objs =
    lkcpp::realloc_objs<instance_counter>(nullptr, 0, 10);
  EXPECT_EQ(10, instance_counter::instance_count());
  lkcpp::dealloc_objs(objs, 10);
}

TEST(test_alloc, dealloc_nullptr)
{
  instance_counter* p = nullptr;
  EXPECT_NO_FATAL_FAILURE(lkcpp::dealloc(p));
  EXPECT_NO_FATAL_FAILURE(lkcpp::dealloc_objs(p, 0));
}

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
  big_object* last = p;
  auto keep_reallocing = [&p, &size, &last]() {
    while (true) {
      p = lkcpp::realloc(p, size + 1000);
      last = p;
      size += 1000;
    }
  };
  EXPECT_THROW(keep_reallocing(), lkcpp::failed_allocation_exception);
  lkcpp::dealloc(p);
}