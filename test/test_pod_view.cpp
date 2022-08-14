#include "lkcpp/algorithm.hpp"
#include "lkcpp/pod.hpp"
#include "lkcpp/pod_view.hpp"

#include "gtest/gtest.h"

namespace {
class test_pod_view : public ::testing::Test {
protected:
  virtual void SetUp() override
  {
    for (int i = 0; i < m_pod.size(); i++) { m_pod[i] = 'a' + i; }
  }

  lkcpp::pod m_pod{10};
};
} // namespace

TEST_F(test_pod_view, default_construct)
{
  lkcpp::pod_view pv;
  EXPECT_EQ(0, pv.size());
  EXPECT_EQ(nullptr, pv.data());
}

TEST_F(test_pod_view, pod_construct)
{
  lkcpp::pod_view pv = m_pod;
  EXPECT_EQ(m_pod.size(), pv.size());
  EXPECT_EQ(m_pod.data(), pv.data());
}

TEST_F(test_pod_view, construct_with_offset)
{
  lkcpp::pod_view pv(m_pod, 2);
  EXPECT_EQ(8, pv.size());
}

TEST_F(test_pod_view, destruct)
{
  lkcpp::pod_view pv = m_pod;
  pv.~pod_view();
  EXPECT_NO_FATAL_FAILURE(m_pod.~pod());
}

TEST_F(test_pod_view, clear)
{
  lkcpp::pod_view pv = m_pod;
  pv.clear();
  EXPECT_NO_FATAL_FAILURE(m_pod.clear());
}

TEST_F(test_pod_view, resize)
{
  lkcpp::pod_view pv = m_pod;
  pv.resize(2);
  EXPECT_EQ(2, pv.size());
}

TEST_F(test_pod_view, add_assign)
{
  lkcpp::pod_view pv = m_pod;
  pv += 2;
  EXPECT_EQ(8, pv.size());
  EXPECT_EQ(2, pv.bytes() - m_pod.bytes());
}

TEST_F(test_pod_view, sub_assign)
{
  lkcpp::pod_view pv(m_pod, 5);
  pv -= 2;
  EXPECT_EQ(7, pv.size());
  EXPECT_EQ(3, pv.bytes() - m_pod.bytes());
}

TEST_F(test_pod_view, compare)
{
  lkcpp::pod_view pv(m_pod);
  EXPECT_EQ(pv, pv);
  lkcpp::pod_view pv2 = pv;
  pv2 += 1;
  EXPECT_NE(pv, pv2);
}

TEST_F(test_pod_view, rshift)
{
  lkcpp::pod_view pv(m_pod, 0, 3);
  pv >> 2;
  char const expected[] = "bcadefghij";
  EXPECT_TRUE(lkcpp::equal(expected, expected + 10, m_pod.bytes()));
}

TEST_F(test_pod_view, lshift)
{
  lkcpp::pod_view pv(m_pod, 0, 3);
  pv << 2;
  char const expected[] = "cabdefghij";
  EXPECT_TRUE(lkcpp::equal(expected, expected + 10, m_pod.bytes()));
}