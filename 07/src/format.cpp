#include "format.hpp"
#include <cctype>

namespace detail {
    std::string processFormat(const std::string& fmt, const std::vector<std::string>& args) {
        std::ostringstream result;
        size_t i = 0;
        const size_t n = fmt.length();

        while (i < n) {
            if (fmt[i] == '{') {
                if (i + 1 >= n) {
                    throw FormatException("Unclosed brace at position " + std::to_string(i));
                }

                size_t closePos = i + 1;
                while (closePos < n && fmt[closePos] != '}') {
                    closePos++;
                }

                if (closePos >= n) {
                    throw FormatException("Unclosed brace at position " + std::to_string(i));
                }

                std::string indexStr = fmt.substr(i + 1, closePos - i - 1);
                if (indexStr.empty()) {
                    throw FormatException("Empty braces at position " + std::to_string(i));
                }

                for (char c : indexStr) {
                    if (!std::isdigit(static_cast<unsigned char>(c))) {
                        throw FormatException("Invalid argument index '" + indexStr +
                                              "' at position " + std::to_string(i));
                    }
                }

                size_t index;
                try {
                    index = std::stoull(indexStr);
                } catch (...) {
                    throw FormatException("Invalid argument index '" + indexStr +
                                          "' at position " + std::to_string(i));
                }

                if (index >= args.size()) {
                    throw FormatException("Argument index " + std::to_string(index) +
                                          " out of range (have " + std::to_string(args.size()) +
                                          " arguments)");
                }

                result << args[index];
                i = closePos + 1;
            } else if (fmt[i] == '}') {
                throw FormatException("Unexpected closing brace at position " + std::to_string(i));
            } else {
                result << fmt[i];
                ++i;
            }
        }

        return result.str();
    }
}