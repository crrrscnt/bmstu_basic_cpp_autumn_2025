#include <gtest/gtest.h>
#include "../src/mybigint.hpp"
#include <sstream>

TEST(BigIntTest, Constructors) {
    std::stringstream ss;
    BigInt a;
    ss << a;
    EXPECT_EQ(ss.str(), "0");
    ss.str("");

    BigInt b(-456);
    ss << b;
    EXPECT_EQ(ss.str(), "-456");
    ss.str("");

    BigInt c("0123789");
    ss << c;
    EXPECT_EQ(ss.str(), "123789");
}

TEST(BigIntTest, CopyMove) {
    std::stringstream ss;
    BigInt a("123");
    BigInt b(a);
    BigInt c = a;
    ss << b;
    EXPECT_EQ(ss.str(), "123");
    ss.str("");

    ss << c;
    EXPECT_EQ(ss.str(), "123");
    ss.str("");

    BigInt d("987");
    BigInt e(std::move(c));
    BigInt f = d;
    ss << d;
    EXPECT_EQ(ss.str(), "987");
    ss.str("");

    ss << f;
    EXPECT_EQ(ss.str(), "987");
}

TEST(BigIntTest, Addition) {
    std::stringstream ss;
    BigInt a("123");
    ss << (a + 456);
    EXPECT_EQ(ss.str(), "579");
    ss.str("");

    ss << (BigInt("-123") + BigInt("-456"));
    EXPECT_EQ(ss.str(), "-579");
    ss.str("");

    ss << (BigInt("123") + BigInt("-456"));
    EXPECT_EQ(ss.str(), "-333");
    ss.str("");

    ss << (BigInt("999999999999999999999") + BigInt("1"));
    EXPECT_EQ(ss.str(), "1000000000000000000000");
}

TEST(BigIntTest, Subtraction) {
    std::stringstream ss;

    ss << (BigInt("100") - 50);
    EXPECT_EQ(ss.str(), "50");
    ss.str("");

    ss << (BigInt("123") - BigInt("456"));
    EXPECT_EQ(ss.str(), "-333");
    ss.str("");

    ss << (BigInt("123") - BigInt("123"));
    EXPECT_EQ(ss.str(), "0");
}

TEST(BigIntTest, Multiplication) {
    std::stringstream ss;
    ss << ((BigInt("1") * 4) * BigInt("2"));
    EXPECT_EQ(ss.str(), "8");
    ss.str("");

    ss << (BigInt("-1") * BigInt("456"));
    EXPECT_EQ(ss.str(), "-456");
    ss.str("");

    ss << (BigInt("123") * BigInt("0"));
    EXPECT_EQ(ss.str(), "0");
    ss.str("");

    ss << (BigInt("123456789") * BigInt("987654321"));
    EXPECT_EQ(ss.str(), "121932631112635269");
}

TEST(BigIntTest, UnaryMinus) {
    std::stringstream ss;
    ss << (-BigInt("1"));
    EXPECT_EQ(ss.str(), "-1");
    ss.str("");

    ss << (-BigInt("-2"));
    EXPECT_EQ(ss.str(), "2");
    ss.str("");

    ss << (-BigInt("0"));
    EXPECT_EQ(ss.str(), "0");
}

TEST(BigIntTest, EqualityOperator) {
    BigInt a("123");
    BigInt b("123");
    BigInt c("456");
    BigInt d("987");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a != b);

    EXPECT_TRUE(a < c);
    EXPECT_TRUE(d > c);

    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a >= b);
}
