#include <gtest/gtest.h>
#include <sxxpr.hpp>

using namespace sxx;

TEST(Sexpr, as_str)
{
  Sexpr sexpr("foo");
  ASSERT_STREQ("foo", sexpr.as_str()->c_str());
}

TEST(ToText, list_size_one)
{
	Pair sexpr(std::make_shared<Sexpr>("foo"), Sexpr::empty);
	ASSERT_EQ(*Sexpr::empty, *sexpr.cdr());
	ASSERT_STREQ("foo", sexpr.car()->as_str()->c_str());
	ASSERT_STREQ("foo", sexpr.car()->to_text().c_str());
	ASSERT_STREQ("(foo)", sexpr.to_text().c_str());
}

TEST(ToText, list_size_two)
{
	auto two = std::make_shared<Pair>(std::make_shared<Sexpr>("bar"), Sexpr::empty);
	Pair one(std::make_shared<Sexpr>("foo"), two);
	ASSERT_STREQ("foo", one.car()->to_text().c_str());
	ASSERT_STREQ("(bar)", one.cdr()->to_text().c_str());
	ASSERT_STREQ("(foo bar)", one.to_text().c_str());
}

TEST(ToText, dotted_pair)
{
	Pair sexpr(std::make_shared<Sexpr>("foo"), std::make_shared<Sexpr>("bar"));
	ASSERT_STREQ("(foo . bar)", sexpr.to_text().c_str());
}


TEST(ToText, list_size_three)
{
    auto three = std::make_shared<Pair>(std::make_shared<Sexpr>("baz"), Sexpr::empty);
    auto two = std::make_shared<Pair>(std::make_shared<Sexpr>("bar"), three);
	Pair one(std::make_shared<Sexpr>("foo"), two);
    ASSERT_STREQ("(foo bar baz)", one.to_text().c_str());
}

TEST(ToText, list_size_three_dotted)
{
    auto two = std::make_shared<Pair>(
            std::make_shared<Sexpr>("bar"),
            std::make_shared<Sexpr>("baz"));
	Pair one(std::make_shared<Sexpr>("foo"), two);
    ASSERT_STREQ("(foo bar . baz)", one.to_text().c_str());
}
