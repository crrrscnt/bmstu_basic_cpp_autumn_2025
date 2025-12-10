#include <gtest/gtest.h>
#include "../src/format.hpp"

// Тесты базовой функциональности
TEST(FormatTest, BasicFormatting) {
    auto text = format("{1}+{1} = {0}", 2, "one");
    EXPECT_EQ(text, "one+one = 2");
}

TEST(FormatTest, SingleArgument) {
    auto text = format("Hello, {0}!", "World");
    EXPECT_EQ(text, "Hello, World!");
}

TEST(FormatTest, MultipleArguments) {
    auto text = format("{0} {1} {2}", "a", "b", "c");
    EXPECT_EQ(text, "a b c");
}

TEST(FormatTest, RepeatedArguments) {
    auto text = format("{0} {0} {0}", "repeat");
    EXPECT_EQ(text, "repeat repeat repeat");
}

TEST(FormatTest, NoPlaceholders) {
    auto text = format("plain text", "unused");
    EXPECT_EQ(text, "plain text");
}

TEST(FormatTest, EmptyString) {
    auto text = format("", "arg");
    EXPECT_EQ(text, "");
}

TEST(FormatTest, OnlyPlaceholder) {
    auto text = format("{0}", 42);
    EXPECT_EQ(text, "42");
}

// Тесты с различными типами данных
TEST(FormatTest, IntegerTypes) {
    auto text = format("{0} {1} {2}", 123, -456, 0);
    EXPECT_EQ(text, "123 -456 0");
}

TEST(FormatTest, FloatingPointTypes) {
    auto text = format("{0} {1}", 3.14, -2.5);
    EXPECT_EQ(text, "3.14 -2.5");
}

TEST(FormatTest, MixedTypes) {
    auto text = format("{0} {1} {2} {3}", 42, "text", 3.14, 'A');
    EXPECT_EQ(text, "42 text 3.14 A");
}

TEST(FormatTest, BooleanType) {
    auto text = format("{0} {1}", true, false);
    EXPECT_EQ(text, "1 0");
}

TEST(FormatTest, CharType) {
    auto text = format("{0}{1}{2}", 'A', 'B', 'C');
    EXPECT_EQ(text, "ABC");
}

// Тесты на исключения - некорректные скобки
TEST(FormatTest, UnclosedBrace) {
    EXPECT_THROW({
        format("{0", "arg");
    }, FormatException);
}

TEST(FormatTest, UnexpectedClosingBrace) {
    EXPECT_THROW({
        format("text }", "arg");
    }, FormatException);
}

TEST(FormatTest, EmptyBraces) {
    EXPECT_THROW({
        format("{}", "arg");
    }, FormatException);
}

TEST(FormatTest, InvalidBraceContent) {
    EXPECT_THROW({
        format("{abc}", "arg");
    }, FormatException);
}

TEST(FormatTest, BraceWithSpace) {
    EXPECT_THROW({
        format("{0 }", "arg");
    }, FormatException);
}

TEST(FormatTest, NegativeIndex) {
    EXPECT_THROW({
        format("{-1}", "arg");
    }, FormatException);
}

// Тесты на исключения - некорректные индексы
TEST(FormatTest, IndexOutOfRange) {
    EXPECT_THROW({
        format("{5}", "arg1", "arg2");
    }, FormatException);
}

TEST(FormatTest, IndexOutOfRangeWithNoArgs) {
    EXPECT_THROW({
        format("{0}");
    }, FormatException);
}

TEST(FormatTest, LargeIndexOutOfRange) {
    EXPECT_THROW({
        format("{100}", "arg");
    }, FormatException);
}

// Тесты на граничные случаи
TEST(FormatTest, MultipleConsecutivePlaceholders) {
    auto text = format("{0}{1}{2}", "a", "b", "c");
    EXPECT_EQ(text, "abc");
}

TEST(FormatTest, TextBetweenPlaceholders) {
    auto text = format("{0} and {1} and {2}", 1, 2, 3);
    EXPECT_EQ(text, "1 and 2 and 3");
}

TEST(FormatTest, PlaceholderAtEnd) {
    auto text = format("Result: {0}", 42);
    EXPECT_EQ(text, "Result: 42");
}

TEST(FormatTest, PlaceholderAtBeginning) {
    auto text = format("{0} is the answer", 42);
    EXPECT_EQ(text, "42 is the answer");
}

TEST(FormatTest, LargeNumberOfArguments) {
    auto text = format("{0}{1}{2}{3}{4}", "a", "b", "c", "d", "e");
    EXPECT_EQ(text, "abcde");
}

TEST(FormatTest, ReverseOrderArguments) {
    auto text = format("{2} {1} {0}", "c", "b", "a");
    EXPECT_EQ(text, "a b c");
}

// Тесты с специальными строками
TEST(FormatTest, StringWithNewlines) {
    auto text = format("Line1\n{0}\nLine2", "Middle");
    EXPECT_EQ(text, "Line1\nMiddle\nLine2");
}

TEST(FormatTest, StringWithTabs) {
    auto text = format("Before\t{0}\tAfter", "Tab");
    EXPECT_EQ(text, "Before\tTab\tAfter");
}

// Тест сообщений исключений
TEST(FormatTest, ExceptionMessageUnclosedBrace) {
    try {
        format("{0", "arg");
        FAIL() << "Expected FormatException";
    } catch (const FormatException& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Unclosed brace") != std::string::npos);
    }
}

TEST(FormatTest, ExceptionMessageUnexpectedClosing) {
    try {
        format("}", "arg");
        FAIL() << "Expected FormatException";
    } catch (const FormatException& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Unexpected closing brace") != std::string::npos);
    }
}

TEST(FormatTest, ExceptionMessageOutOfRange) {
    try {
        format("{5}", "arg");
        FAIL() << "Expected FormatException";
    } catch (const FormatException& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("out of range") != std::string::npos);
    }
}