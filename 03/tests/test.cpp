#include <gtest/gtest.h>
#include "../src/parser.hpp"
#include <string>
#include <vector>

#include <limits>
// #include <algorithm>

std::vector<std::string> string_stat;
std::vector<std::uint64_t> digit_stat;

int string_token_counter = 0;
int digit_token_counter = 0;

void test_string_parse(const std::string& token){
    string_stat.push_back(token);
    ++string_token_counter;
};
void test_digit_parse(const std::uint64_t& token){
    digit_stat.push_back(token);
    ++digit_token_counter;
};

func_digit_ptr ptr_digit = test_digit_parse;
func_str_ptr ptr_string = test_string_parse;

TEST(Parser, EmptySuccess) {
    std::string line = "";
    EXPECT_NO_THROW(parse(line));
    EXPECT_TRUE(string_stat.empty());
    EXPECT_TRUE(digit_stat.empty());
}

TEST(Parser, TokensNoCallback) {
    string_stat.clear();
    digit_stat.clear();
    std::string line= "abc 123";
    parse(line);
    EXPECT_TRUE(string_stat.empty());
    EXPECT_TRUE(digit_stat.empty());
}

TEST(Parser, TokensCallback) {
    parse("12345\nLOREM IPSUM  9iu5ight6ii\t\n\n \t ou88889\n\t2", ptr_digit, ptr_string);
    ASSERT_EQ(digit_stat.size(), static_cast<size_t>(2));
    EXPECT_EQ(digit_stat[0], static_cast<std::uint64_t>(12345));
    EXPECT_EQ(digit_stat[1], static_cast<std::uint64_t>(2));
    ASSERT_EQ(string_stat.size(), static_cast<size_t>(4));
    EXPECT_EQ(string_stat[0], "LOREM");
    EXPECT_EQ(string_stat[1], "IPSUM");
    EXPECT_EQ(string_stat[2], "9iu5ight6ii");
    EXPECT_EQ(string_stat[3], "ou88889");

    string_token_counter = 0;
    digit_token_counter = 0;
    string_stat.clear();
    digit_stat.clear();
}


TEST(Parser, CheckOverflowLimitForUint64) { // в string должно уйти
    // UINT64_MAX 18446744073709551615
    std::string line = "18446744073709551616";
    parse(line, ptr_digit, ptr_string);
    EXPECT_TRUE(digit_stat.empty());
    EXPECT_TRUE(!string_stat.empty());
    EXPECT_EQ(string_stat[0], "18446744073709551616");

    string_token_counter = 0;
    digit_token_counter = 0;
    string_stat.clear();
    digit_stat.clear();
}

TEST(Parser, NoStringCallback) { // нет stringcallback
    // UINT64_MAX 18446744073709551615
    std::string line = "18446744073709551616";
    parse(line, ptr_digit);
    EXPECT_TRUE(digit_stat.empty());
    EXPECT_TRUE(string_stat.empty());

    string_token_counter = 0;
    digit_token_counter = 0;
    string_stat.clear();
    digit_stat.clear();
}

TEST(Parser, LimitForUint64ToDigit) {
    std::string line = std::to_string(UINT64_MAX);
    parse(line, ptr_digit);
    EXPECT_TRUE(!digit_stat.empty());
    EXPECT_TRUE(string_stat.empty());
    EXPECT_EQ(digit_stat[0], UINT64_MAX);

    string_token_counter = 0;
    digit_token_counter = 0;
    string_stat.clear();
    digit_stat.clear();
}
