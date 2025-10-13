#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cctype>
#include <cstdint>
#include <string>

using func_ptr = void(*)();
using func_digit_ptr = void(*)(const std::uint64_t&);
using func_str_ptr = void(*)(const std::string&);

void parse(const std::string& text,
           func_digit_ptr digit_callback = nullptr,
           func_str_ptr string_callback = nullptr);

#endif // PARSER_H