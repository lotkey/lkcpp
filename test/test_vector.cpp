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
  EXPECT_THROW(x[1], lkcpp::out_of_bounds_exception);
}

class Test_object_construction {
public:
  static int count() { return s_num_instances; }

  Test_object_construction() { s_num_instances++; }
  Test_object_construction(int i) : m_i(i) { s_num_instances++; }
  ~Test_object_construction() { s_num_instances--; }

  operator int() const { return m_i; }

  int get_int() const { return m_i; }

private:
  static int s_num_instances;

  int m_i = 0;
};
int Test_object_construction::s_num_instances = 0;

TEST(test_vector, push_and_pop)
{
  lkcpp::vector<Test_object_construction> v;
  EXPECT_EQ(0, Test_object_construction::count());
  EXPECT_EQ(0, v.size());

  v.push_back(1);

  EXPECT_EQ(1, Test_object_construction::count());
  EXPECT_EQ(1, v.back().get_int());
  EXPECT_EQ(1, v.size());

  v.pop_back();
  EXPECT_EQ(0, Test_object_construction::count());
  EXPECT_EQ(0, v.size());
}

TEST(test_vector, insert_and_erase)
{
  lkcpp::vector<Test_object_construction> v;

  EXPECT_EQ(0, Test_object_construction::count());
  EXPECT_EQ(0, v.size());

  for (int i = 0; i < 10; i++) { v.insert(i, i); }

  EXPECT_EQ(10, v.size());
  EXPECT_EQ(10, Test_object_construction::count());

  v.erase(4, 8);
  EXPECT_EQ(6, v.size());
  EXPECT_EQ(6, Test_object_construction::count());

  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(2, v[2]);
  EXPECT_EQ(3, v[3]);
}