#include <gtest/gtest.h>
#include "../src/BigInt.hpp"
#include <sstream>

TEST(BigIntTest, DefaultConstructor) {
    BigInt a;
    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "0");
}

TEST(BigIntTest, Int32Constructor) {
    BigInt a(123);
    BigInt b(-456);
    BigInt c(0);

    std::stringstream ss1, ss2, ss3;
    ss1 << a;
    ss2 << b;
    ss3 << c;

    EXPECT_EQ(ss1.str(), "123");
    EXPECT_EQ(ss2.str(), "-456");
    EXPECT_EQ(ss3.str(), "0");
}

TEST(BigIntTest, StringConstructor) {
    BigInt a("123456789012345678901234567890");
    BigInt b("-987654321098765432109876543210");
    BigInt c("0");
    BigInt d("000123");

    std::stringstream ss1, ss2, ss3, ss4;
    ss1 << a;
    ss2 << b;
    ss3 << c;
    ss4 << d;

    EXPECT_EQ(ss1.str(), "123456789012345678901234567890");
    EXPECT_EQ(ss2.str(), "-987654321098765432109876543210");
    EXPECT_EQ(ss3.str(), "0");
    EXPECT_EQ(ss4.str(), "123");
}

// Тесты копирования и перемещения
TEST(BigIntTest, CopyConstructor) {
    BigInt a("123456789");
    BigInt b(a);

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "123456789");
}

TEST(BigIntTest, MoveConstructor) {
    BigInt a("123456789");
    BigInt b(std::move(a));

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "123456789");
}

TEST(BigIntTest, CopyAssignment) {
    BigInt a("123456789");
    BigInt b;
    b = a;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "123456789");
}

TEST(BigIntTest, MoveAssignment) {
    BigInt a("123456789");
    BigInt b;
    b = std::move(a);

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "123456789");
}

// Тесты сложения
TEST(BigIntTest, AdditionPositive) {
    BigInt a("123");
    BigInt b("456");
    BigInt c = a + b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "579");
}

TEST(BigIntTest, AdditionWithInt) {
    BigInt a("100");
    BigInt b = a + 50;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "150");
}

TEST(BigIntTest, AdditionNegative) {
    BigInt a("-123");
    BigInt b("-456");
    BigInt c = a + b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "-579");
}

TEST(BigIntTest, AdditionMixed) {
    BigInt a("123");
    BigInt b("-456");
    BigInt c = a + b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "-333");
}

TEST(BigIntTest, AdditionLargeNumbers) {
    BigInt a("999999999999999999999");
    BigInt b("1");
    BigInt c = a + b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "1000000000000000000000");
}

// Тесты вычитания
TEST(BigIntTest, SubtractionPositive) {
    BigInt a("456");
    BigInt b("123");
    BigInt c = a - b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "333");
}

TEST(BigIntTest, SubtractionWithInt) {
    BigInt a("100");
    BigInt b = a - 50;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "50");
}

TEST(BigIntTest, SubtractionNegativeResult) {
    BigInt a("123");
    BigInt b("456");
    BigInt c = a - b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "-333");
}

TEST(BigIntTest, SubtractionToZero) {
    BigInt a("123");
    BigInt b("123");
    BigInt c = a - b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "0");
}

// Тесты умножения
TEST(BigIntTest, MultiplicationPositive) {
    BigInt a("123");
    BigInt b("456");
    BigInt c = a * b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "56088");
}

TEST(BigIntTest, MultiplicationWithInt) {
    BigInt a("100");
    BigInt b = a * 5;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "500");
}

TEST(BigIntTest, MultiplicationNegative) {
    BigInt a("-123");
    BigInt b("456");
    BigInt c = a * b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "-56088");
}

TEST(BigIntTest, MultiplicationByZero) {
    BigInt a("123");
    BigInt b("0");
    BigInt c = a * b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "0");
}

TEST(BigIntTest, MultiplicationLarge) {
    BigInt a("123456789");
    BigInt b("987654321");
    BigInt c = a * b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "121932631112635269");
}

// Тесты унарного минуса
TEST(BigIntTest, UnaryMinus) {
    BigInt a("123");
    BigInt b = -a;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "-123");
}

TEST(BigIntTest, UnaryMinusNegative) {
    BigInt a("-123");
    BigInt b = -a;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "123");
}

TEST(BigIntTest, UnaryMinusZero) {
    BigInt a("0");
    BigInt b = -a;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "0");
}

// Тесты сравнения
TEST(BigIntTest, EqualityOperator) {
    BigInt a("123");
    BigInt b("123");
    BigInt c("456");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(BigIntTest, InequalityOperator) {
    BigInt a("123");
    BigInt b("456");

    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != a);
}

TEST(BigIntTest, LessThanOperator) {
    BigInt a("123");
    BigInt b("456");
    BigInt c("-789");

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(c < a);
}

TEST(BigIntTest, LessOrEqualOperator) {
    BigInt a("123");
    BigInt b("123");
    BigInt c("456");

    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(c <= a);
}

TEST(BigIntTest, GreaterThanOperator) {
    BigInt a("456");
    BigInt b("123");

    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

TEST(BigIntTest, GreaterOrEqualOperator) {
    BigInt a("456");
    BigInt b("456");
    BigInt c("123");

    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_FALSE(c >= a);
}

// Комплексный тест из примера
TEST(BigIntTest, ComplexExample) {
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);
    a = d + b;

    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "246913578024691357802469135782");
}

TEST(BigIntTest, LargeNumberAddition) {
    BigInt a("99999999999999999999999999999999");
    BigInt b("1");
    BigInt c = a + b;

    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "100000000000000000000000000000000");
}

TEST(BigIntTest, NegativeZero) {
    BigInt a("0");
    BigInt b = -a;

    std::stringstream ss;
    ss << b;
    EXPECT_EQ(ss.str(), "0");
}

TEST(BigIntTest, ChainedOperations) {
    BigInt a("10");
    BigInt b("20");
    BigInt c("30");
    BigInt result = a + b + c;

    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "60");
}