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
    // symbols pointing to same string
    auto foo = std::make_shared<const std::string>("foo");
    ASSERT_EQ(Symbol(foo), Symbol(foo));

    // symbols pointing to different string objects
    // and compared through sexprs
    Sexpr s1(Symbol(std::string("foo")));
    Sexpr s2(Symbol(std::string("foo")));
    ASSERT_EQ(s1, s2);
}

TEST(ToText, list_size_one)
{
    Sexpr sexpr(make(Symbol("foo")), nil);
    ASSERT_EQ(Sexpr::empty, *sexpr.rest());
    ASSERT_STREQ("foo", sexpr.first()->as_symbol().c_str());
    ASSERT_STREQ("foo", sexpr.first()->to_text().c_str());
    ASSERT_STREQ("(foo)", sexpr.to_text().c_str());
}

TEST(ToText, list_size_two)
{
    Sexpr two(make("bar"), nil);
    Sexpr one(make("foo"), make(two));
    ASSERT_EQ(two, *one.rest());
    ASSERT_FALSE(one.rest()->is_empty());
    ASSERT_TRUE(one.rest()->is_pair());
    ASSERT_STREQ("\"foo\"", one.first()->to_text().c_str());
    ASSERT_STREQ("(\"bar\")", one.rest()->to_text().c_str());
    ASSERT_STREQ("(\"foo\" \"bar\")", one.to_text().c_str());
}

TEST(ToText, dotted_pair)
{
    Sexpr sexpr(make(Symbol("foo")), make("bar"));
    ASSERT_STREQ("(foo . \"bar\")", sexpr.to_text().c_str());
}

TEST(ToText, list_size_three)
{
    auto three = make(make("baz"), nil);
    auto two = make(make("bar"), three);
    Sexpr one(make("foo"), two);
    ASSERT_STREQ("(\"foo\" \"bar\" \"baz\")", one.to_text().c_str());
}

TEST(ToText, list_size_three_dotted)
{
    auto two = make(
        make(Symbol("bar")),
        make(Symbol("baz")));
    Sexpr one(make(Symbol("foo")), two);
    ASSERT_STREQ("(foo bar . baz)", one.to_text().c_str());
}
