#include "lkcpp/type_traits.hpp"

#include "gtest/gtest.h"

TEST(test_type_traits, integral_constant)
{
  EXPECT_EQ(true, lkcpp::true_type::value);
  EXPECT_EQ(false, lkcpp::false_type::value);
}

TEST(test_type_traits, is_pointer)
{
  EXPECT_EQ(false, lkcpp::is_pointer<int>::value);
  EXPECT_EQ(true, lkcpp::is_pointer<int*>::value);
  EXPECT_EQ(true, lkcpp::is_pointer<int const*>::value);
  EXPECT_EQ(true, lkcpp::is_pointer<int* const>::value);
  EXPECT_EQ(true, lkcpp::is_pointer<int const* const>::value);
  EXPECT_EQ(true, lkcpp::is_pointer<int**>::value);
}

TEST(test_type_traits, is_void)
{
  EXPECT_EQ(true, lkcpp::is_void<void>::value);
  EXPECT_EQ(false, lkcpp::is_void<int>::value);
}

TEST(test_type_traits, is_array)
{
  EXPECT_EQ(true, lkcpp::is_array<int[]>::value);
  EXPECT_EQ(true, lkcpp::is_array<int const[]>::value);
  EXPECT_EQ(true, lkcpp::is_array<int[1]>::value);
  EXPECT_EQ(true, lkcpp::is_array<int[][1]>::value);
  EXPECT_EQ(true, lkcpp::is_array<int[1][1]>::value);
  EXPECT_EQ(false, lkcpp::is_array<int>::value);
  EXPECT_EQ(true, lkcpp::is_array_v<int[]>);
  EXPECT_EQ(true, lkcpp::is_array_v<int const[]>);
  EXPECT_EQ(true, lkcpp::is_array_v<int[1]>);
  EXPECT_EQ(true, lkcpp::is_array_v<int[][1]>);
  EXPECT_EQ(true, lkcpp::is_array_v<int[1][1]>);
  EXPECT_EQ(false, lkcpp::is_array_v<int>);
}

TEST(test_type_traits, is_null_pointer)
{
  EXPECT_EQ(true, lkcpp::is_null_pointer<lkcpp::nullptr_t>::value);
  EXPECT_EQ(false, lkcpp::is_null_pointer<int>::value);
}

TEST(test_type_traits, is_integral)
{
  EXPECT_EQ(true, lkcpp::is_integral<char const>::value);
  EXPECT_EQ(true, lkcpp::is_integral<char>::value);
  EXPECT_EQ(true, lkcpp::is_integral<unsigned char>::value);
  EXPECT_EQ(true, lkcpp::is_integral<signed char>::value);
  EXPECT_EQ(true, lkcpp::is_integral<int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<unsigned int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<signed int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<short int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<unsigned short int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<signed short int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<long int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<signed long int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<unsigned long int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<long long int>::value);
  EXPECT_EQ(true, lkcpp::is_integral<unsigned long long int>::value);
  EXPECT_EQ(false, lkcpp::is_integral<float>::value);
  EXPECT_EQ(false, lkcpp::is_integral<double>::value);
  EXPECT_EQ(false, lkcpp::is_integral<long double>::value);
  EXPECT_EQ(true, lkcpp::is_integral<wchar_t>::value);
}

TEST(test_type_traits, is_floating_point)
{
  EXPECT_EQ(false, lkcpp::is_floating_point<char const>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<char>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<unsigned char>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<signed char>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<unsigned int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<signed int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<short int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<unsigned short int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<signed short int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<long int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<signed long int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<unsigned long int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<long long int>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<unsigned long long int>::value);
  EXPECT_EQ(true, lkcpp::is_floating_point<float>::value);
  EXPECT_EQ(true, lkcpp::is_floating_point<double>::value);
  EXPECT_EQ(true, lkcpp::is_floating_point<long double>::value);
  EXPECT_EQ(false, lkcpp::is_floating_point<wchar_t>::value);
}

TEST(test_type_traits, is_lvalue_reference)
{
  EXPECT_EQ(false, lkcpp::is_lvalue_reference<char>::value);
  EXPECT_EQ(false, lkcpp::is_lvalue_reference<char const>::value);
  EXPECT_EQ(true, lkcpp::is_lvalue_reference<int&>::value);
  EXPECT_EQ(true, lkcpp::is_lvalue_reference<int const&>::value);
  EXPECT_EQ(false, lkcpp::is_lvalue_reference<int&&>::value);
  EXPECT_EQ(false, lkcpp::is_lvalue_reference<int const&&>::value);
}

TEST(test_type_traits, is_rvalue_reference)
{
  EXPECT_EQ(false, lkcpp::is_rvalue_reference<char>::value);
  EXPECT_EQ(false, lkcpp::is_rvalue_reference<char const>::value);
  EXPECT_EQ(false, lkcpp::is_rvalue_reference<int&>::value);
  EXPECT_EQ(false, lkcpp::is_rvalue_reference<int const&>::value);
  EXPECT_EQ(true, lkcpp::is_rvalue_reference<int&&>::value);
  EXPECT_EQ(true, lkcpp::is_rvalue_reference<int const&&>::value);
}

TEST(test_type_traits, is_reference)
{
  EXPECT_EQ(false, lkcpp::is_reference<char>::value);
  EXPECT_EQ(false, lkcpp::is_reference<char const>::value);
  EXPECT_EQ(true, lkcpp::is_reference<int&>::value);
  EXPECT_EQ(true, lkcpp::is_reference<int const&>::value);
  EXPECT_EQ(true, lkcpp::is_reference<int&&>::value);
  EXPECT_EQ(true, lkcpp::is_reference<int const&&>::value);
}

TEST(test_type_traits, is_const)
{
  EXPECT_EQ(false, lkcpp::is_const_v<char>);
  EXPECT_EQ(false, lkcpp::is_const<char>::value);
  EXPECT_EQ(true, lkcpp::is_const<char const>::value);
  EXPECT_EQ(false, lkcpp::is_const<char const*>::value);
  EXPECT_EQ(true, lkcpp::is_const<char const* const>::value);
}

TEST(test_type_traits, pointer_depth)
{
  EXPECT_EQ(0, lkcpp::pointer_depth<char>::value);
  EXPECT_EQ(1, lkcpp::pointer_depth<char*>::value);
  EXPECT_EQ(2, lkcpp::pointer_depth<char**>::value);
  EXPECT_EQ(0, lkcpp::pointer_depth_v<char>);
  EXPECT_EQ(1, lkcpp::pointer_depth_v<char*>);
  EXPECT_EQ(2, lkcpp::pointer_depth_v<char**>);
}

TEST(test_type_traits, array_depth)
{
  EXPECT_EQ(0, lkcpp::array_depth<char>::value);
  EXPECT_EQ(1, lkcpp::array_depth<char const[]>::value);
  EXPECT_EQ(2, lkcpp::array_depth<char[][1]>::value);
}