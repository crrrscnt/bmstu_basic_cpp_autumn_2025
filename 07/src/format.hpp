#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

class FormatException : public std::runtime_error {
public:
    explicit FormatException(const std::string& message) : std::runtime_error(message) {}
};

namespace detail {
    inline std::string toString(const std::string& s) { return s; }

    template<typename T>
    inline std::string toString(const T& v) {
        std::ostringstream oss;
        oss << v;
        return oss.str();
    }

    std::string processFormat(const std::string& fmt, const std::vector<std::string>& args);
}

template<typename... Args>
std::string format(const std::string& fmt, Args&&... args) {
    std::vector<std::string> argStrings;
    argStrings.reserve(sizeof...(Args));
    (void)std::initializer_list<int>{ (argStrings.push_back(detail::toString(std::forward<Args>(args))), 0)... };
    return detail::processFormat(fmt, argStrings);
}
#endif // FORMAT_HPP