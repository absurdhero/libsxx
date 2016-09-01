#include <gtest/gtest.h>
#include <sxxpr.hpp>

TEST(Sexpr, as_str)
{
  Sexpr sexpr("foo");
  ASSERT_STREQ("foo", sexpr.as_str()->c_str());
}

TEST(Sexpr, list_size_one)
{
	Sexpr sexpr(std::make_shared<Sexpr>("foo"), Sexpr::empty);
	ASSERT_EQ(*Sexpr::empty, *sexpr.cdr());
	ASSERT_STREQ("foo", sexpr.car()->as_str()->c_str());
	ASSERT_STREQ("foo", sexpr.car()->to_text().c_str());
	ASSERT_STREQ("(foo)", sexpr.to_text().c_str());
}
