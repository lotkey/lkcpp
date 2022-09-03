#include "lkcpp/type_traits.hpp"

#include "gtest/gtest.h"

#include <vector>

namespace {
enum Enum {};
enum class EnumClass {};

class Class {
public:
  Class() = default;
  Class(int) {}
  Class(Class const&) = default;
  Class(Class&&) = default;
  Class& operator=(Class const&) = default;
  Class& operator=(Class&&) = default;

  void f1() {}
  void f2() const {}
  void f3() volatile {}
  void f4() const volatile {}

  int m1;
};

class NonTriviallyCopyable {
public:
  NonTriviallyCopyable(NonTriviallyCopyable const& x) {}
};

class NonConstructible {
public:
  NonConstructible() = delete;
  NonConstructible(NonConstructible const&) = delete;
  NonConstructible(NonConstructible&&) = delete;
  NonConstructible& operator=(NonConstructible const&) = delete;
  NonConstructible& operator=(NonConstructible&&) = delete;
};

union Union {};
struct Struct {};
void function() {}
} // namespace

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
  EXPECT_EQ(true, lkcpp::is_pointer<int* volatile>::value);
  EXPECT_EQ(true, lkcpp::is_pointer<int* const volatile>::value);
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

TEST(test_type_traits, is_enum)
{
  EXPECT_EQ(false, lkcpp::is_enum<int>::value);
  EXPECT_EQ(true, lkcpp::is_enum<Enum>::value);
  EXPECT_EQ(true, lkcpp::is_enum<EnumClass>::value);
}

TEST(test_type_traits, is_union)
{
  EXPECT_EQ(false, lkcpp::is_union<int>::value);
  EXPECT_EQ(true, lkcpp::is_union<Union>::value);
}

TEST(test_type_traits, is_class)
{
  EXPECT_EQ(false, lkcpp::is_class<int>::value);
  EXPECT_EQ(true, lkcpp::is_class<Class>::value);
  EXPECT_EQ(true, lkcpp::is_class<std::vector<int>>::value);
}

TEST(test_type_traits, is_function)
{
  EXPECT_EQ(false, lkcpp::is_function<int>::value);
  EXPECT_EQ(true, lkcpp::is_function<decltype(function)>::value);
}

TEST(test_type_traits, is_member_pointer)
{
  EXPECT_EQ(false, lkcpp::is_member_pointer<int>::value);
  EXPECT_EQ(true, lkcpp::is_member_pointer<int(Class::*)>::value);
}

TEST(test_type_traits, is_member_function_pointer)
{
  EXPECT_EQ(false, lkcpp::is_member_function_pointer_v<int(Class::*)>);
  EXPECT_EQ(false, lkcpp::is_member_function_pointer_v<decltype(function)>);
  EXPECT_EQ(true,
            lkcpp::is_member_function_pointer<decltype(&Class::f1)>::value);
  EXPECT_EQ(true, lkcpp::is_member_function_pointer_v<decltype(&Class::f2)>);
  EXPECT_EQ(true, lkcpp::is_member_function_pointer_v<decltype(&Class::f3)>);
  EXPECT_EQ(true, lkcpp::is_member_function_pointer_v<decltype(&Class::f4)>);
}

TEST(test_type_traits, is_member_object_pointer)
{
  EXPECT_EQ(false, lkcpp::is_member_object_pointer_v<int>);
  EXPECT_EQ(false, lkcpp::is_member_object_pointer_v<decltype(&Class::f1)>);
  EXPECT_EQ(true, lkcpp::is_member_object_pointer_v<decltype(&Class::m1)>);
}

TEST(test_type_traits, is_same)
{
  static constexpr bool b1 = lkcpp::is_same<int, int>::value;
  static constexpr bool b2 = lkcpp::is_same<int, float>::value;
  EXPECT_EQ(true, b1);
  EXPECT_EQ(false, b2);
}

TEST(test_type_traits, is_arithmetic)
{
  EXPECT_EQ(false, lkcpp::is_arithmetic_v<Class>);
  EXPECT_EQ(true, lkcpp::is_arithmetic_v<bool>);
  EXPECT_EQ(true, lkcpp::is_arithmetic_v<int>);
  EXPECT_EQ(true, lkcpp::is_arithmetic_v<int const>);
  EXPECT_EQ(false, lkcpp::is_arithmetic_v<int&>);
  EXPECT_EQ(false, lkcpp::is_arithmetic_v<int*>);
  EXPECT_EQ(true, lkcpp::is_arithmetic_v<float>);
  EXPECT_EQ(true, lkcpp::is_arithmetic_v<float const>);
  EXPECT_EQ(false, lkcpp::is_arithmetic_v<float&>);
  EXPECT_EQ(false, lkcpp::is_arithmetic_v<float*>);
  EXPECT_EQ(true, lkcpp::is_arithmetic_v<char>);
  EXPECT_EQ(true, lkcpp::is_arithmetic_v<char const>);
  EXPECT_EQ(false, lkcpp::is_arithmetic_v<char&>);
  EXPECT_EQ(false, lkcpp::is_arithmetic_v<char*>);
}

TEST(test_type_traits, is_fundamental)
{
  EXPECT_EQ(false, lkcpp::is_fundamental_v<Class>);
  EXPECT_EQ(true, lkcpp::is_fundamental_v<bool>);
  EXPECT_EQ(true, lkcpp::is_fundamental_v<int>);
  EXPECT_EQ(true, lkcpp::is_fundamental_v<int const>);
  EXPECT_EQ(false, lkcpp::is_fundamental_v<int&>);
  EXPECT_EQ(false, lkcpp::is_fundamental_v<int*>);
  EXPECT_EQ(true, lkcpp::is_fundamental_v<float>);
  EXPECT_EQ(true, lkcpp::is_fundamental_v<float const>);
  EXPECT_EQ(false, lkcpp::is_fundamental_v<float&>);
  EXPECT_EQ(false, lkcpp::is_fundamental_v<float*>);
  EXPECT_EQ(true, lkcpp::is_fundamental_v<char>);
  EXPECT_EQ(true, lkcpp::is_fundamental_v<char const>);
  EXPECT_EQ(false, lkcpp::is_fundamental_v<char&>);
  EXPECT_EQ(false, lkcpp::is_fundamental_v<char*>);
}

TEST(test_type_traits, is_scalar)
{
  EXPECT_EQ(true, lkcpp::is_scalar_v<int>);
  EXPECT_EQ(true, lkcpp::is_scalar_v<double>);
  EXPECT_EQ(false, lkcpp::is_scalar_v<Class>);
}

TEST(test_type_traits, is_object)
{
  EXPECT_EQ(true, lkcpp::is_object_v<int>);
  EXPECT_EQ(false, lkcpp::is_object_v<int&>);
  EXPECT_EQ(true, lkcpp::is_object_v<Class>);
  EXPECT_EQ(false, lkcpp::is_object_v<Class&>);
}

TEST(test_type_traits, is_compound)
{
  EXPECT_EQ(true, lkcpp::is_compound_v<Class>);
  EXPECT_EQ(false, lkcpp::is_compound_v<int>);
}

TEST(test_type_traits, is_volatile)
{
  EXPECT_EQ(true, lkcpp::is_volatile_v<int volatile>);
  EXPECT_EQ(false, lkcpp::is_volatile_v<int>);
}

TEST(test_type_traits, is_trivially_copyable)
{
  EXPECT_EQ(true, lkcpp::is_trivially_copyable_v<int>);
  EXPECT_EQ(true, lkcpp::is_trivially_copyable_v<Class>);
  EXPECT_EQ(false, lkcpp::is_trivially_copyable_v<NonTriviallyCopyable>);
}

TEST(test_type_traits, is_constructible)
{
  EXPECT_EQ(true, lkcpp::is_constructible_v<Class>);
  EXPECT_EQ(false, lkcpp::is_constructible_v<NonConstructible>);
}