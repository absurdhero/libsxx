#include <gtest/gtest.h>
#include <sxx/sexpr.hpp>

using namespace sxx;

TEST(Sexpr, as_string)
{
    Sexpr sexpr("foo");
    ASSERT_STREQ("foo", sexpr.as_string().c_str());
}

TEST(Sexpr, str_equals)
{
    Sexpr s1("foo");
    Sexpr s2("foo");
    ASSERT_EQ(s1, s2);
}

TEST(Sexpr, as_symbol)
{
    Sexpr sexpr(Symbol("foo"));
    ASSERT_STREQ("foo", sexpr.as_symbol().c_str());
}

TEST(Sexpr, symbol_equals)
{
    auto foo = std::make_shared<const std::string>("foo");
    Sexpr s1("foo");
    Sexpr s2("foo");
    ASSERT_EQ(s1, s2);
}

TEST(ToText, list_size_one)
{
    List sexpr(make(Symbol("foo")), List::null);
    ASSERT_EQ(Sexpr::empty, *sexpr.rest());
    ASSERT_STREQ("foo", sexpr.first()->as_symbol().c_str());
    ASSERT_STREQ("foo", sexpr.first()->to_text().c_str());
    ASSERT_STREQ("(foo)", sexpr.to_text().c_str());
}

TEST(ToText, list_size_two)
{
    List two(make("bar"), List::null);
    List one(make("foo"), two.sexpr);
    ASSERT_EQ(*two.sexpr, *one.rest());
    ASSERT_FALSE(one.rest()->is_empty());
    ASSERT_TRUE(one.rest()->is_pair());
    ASSERT_STREQ("\"foo\"", one.first()->to_text().c_str());
    ASSERT_STREQ("(\"bar\")", one.rest()->to_text().c_str());
    ASSERT_STREQ("(\"foo\" \"bar\")", one.to_text().c_str());
}

TEST(ToText, dotted_pair)
{
    List sexpr(make(Symbol("foo")), make("bar"));
    ASSERT_STREQ("(foo . \"bar\")", sexpr.to_text().c_str());
}


TEST(ToText, list_size_three)
{
    auto three = std::make_shared<List>(make("baz"), List::null);
    auto two = std::make_shared<List>(make("bar"), three->sexpr);
    List one(make("foo"), two->sexpr);
    ASSERT_STREQ("(\"foo\" \"bar\" \"baz\")", one.to_text().c_str());
}

TEST(ToText, list_size_three_dotted)
{
    auto two = std::make_shared<List>(
        make(Symbol("bar")),
        make(Symbol("baz")));
    List one(make(Symbol("foo")), two->sexpr);
    ASSERT_STREQ("(foo bar . baz)", one.to_text().c_str());
}
