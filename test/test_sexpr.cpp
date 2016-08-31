#include <gtest/gtest.h>
#include <sxxpr.hpp>

TEST(Sexpr, as_str)
{
  Sexpr sexpr("foo");
  ASSERT_STREQ("foo", sexpr.as_str()->c_str());
}

TEST(Sexpr, nullcdr)
{
	Sexpr str("foo");
	Sexpr sexpr(&str, nullptr);
	ASSERT_EQ(nullptr, sexpr.cdr().get());
	ASSERT_EQ(str, *sexpr.car());
}
