#include "parser.hpp"

void parse(const std::string& text,
           func_digit_ptr digit_callback,
           func_str_ptr string_callback)
{
    std::string token;

    auto check_for_digits = [](const std::string& token) {
        for (char c : token) {
            int ascii_val = static_cast<int>(c);
            if (!(ascii_val >= 48 && ascii_val <= 57)) return false;
        }
        return true;
    };

    auto process_token = [&](const std::string& token) {
        if (check_for_digits(token) && !token.empty()) {
            bool is_num = true;
            if (token.length() > 20) is_num = false;
            else if (token.length() == 20) {
                const std::string max_uint64 = "18446744073709551615";
                for (size_t i = 0; i < 20; ++i) {
                    if (token > max_uint64) {
                        is_num = false;
                    }
                }
            }
            if (is_num) {
                std::uint64_t num = std::stoull(token);
                if (digit_callback != nullptr) digit_callback(num);
                } else {
                if (string_callback != nullptr) string_callback(token);
                }
            } else {
                if (string_callback != nullptr) string_callback(token);
            }
    };

    for (char c : text) {
        if (!std::isspace(static_cast<int>(c))) {
            token.push_back(c);
        }
        else {
            if (!token.empty()) {
                process_token(token);
                token.clear();
            };
        };
    }
    process_token(token);
}