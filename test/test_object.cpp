#include "util/instance_counter.hpp"

#include "lkcpp/memory/alloc.hpp"
#include "lkcpp/object.hpp"

#include "gtest/gtest.h"

TEST(test_object, construct_destruct)
{
  auto* p = lkcpp::alloc<instance_counter>();
  lkcpp::construct(p);
  EXPECT_EQ(1, instance_counter::instance_count());
  lkcpp::destruct(p);
  EXPECT_EQ(0, instance_counter::instance_count());
  lkcpp::dealloc(p);
}
