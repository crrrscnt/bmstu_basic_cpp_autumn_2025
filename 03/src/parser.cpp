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
        if (check_for_digits(token)) {
            try {
                std::uint64_t num = std::stoull(token);
                if (digit_callback != nullptr) digit_callback(num);
            } catch (...) {
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