#include "BigInt.hpp"
#include <algorithm>
#include <cstring>

BigInt::BigInt() : digits(nullptr), size(1), negative(false) {
    digits = new int[1];
    digits[0] = 0;
}

BigInt::BigInt(int32_t value) : digits(nullptr), size(0), negative(value < 0) {
    if (value == 0) {
        size = 1;
        digits = new int[1];
        digits[0] = 0;
        negative = false;
        return;
    }

    int32_t abs_value = (value < 0) ? -value : value;

    int32_t temp = abs_value;
    size_t count = 0;
    while (temp > 0) {
        count++;
        temp /= 10;
    }

    size = count;
    digits = new int[size];

    temp = abs_value;
    for (size_t i = 0; i < size; i++) {
        digits[i] = temp % 10;
        temp /= 10;
    }
}

BigInt::BigInt(const std::string& str) : digits(nullptr), size(0), negative(false) {
    if (str.empty() || str == "-") {
        size = 1;
        digits = new int[1];
        digits[0] = 0;
        return;
    }

    size_t start = 0;
    if (str[0] == '-') {
        negative = true;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }

    while (start < str.length() && str[start] == '0') {
        start++;
    }

    if (start == str.length()) {
        size = 1;
        digits = new int[1];
        digits[0] = 0;
        negative = false;
        return;
    }

    size = str.length() - start;
    digits = new int[size];

    for (size_t i = 0; i < size; i++) {
        digits[i] = str[str.length() - 1 - i] - '0';
    }
}

BigInt::BigInt(const BigInt& other) : digits(nullptr), size(other.size), negative(other.negative) {
    digits = new int[size];
    for (size_t i = 0; i < size; i++) {
        digits[i] = other.digits[i];
    }
}

BigInt::BigInt(BigInt&& other) noexcept : digits(other.digits), size(other.size), negative(other.negative) {
    other.digits = nullptr;
    other.size = 0;
    other.negative = false;
}

BigInt::~BigInt() {
    delete[] digits;
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        delete[] digits;
        size = other.size;
        negative = other.negative;
        digits = new int[size];
        for (size_t i = 0; i < size; i++) {
            digits[i] = other.digits[i];
        }
    }
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;
        size = other.size;
        negative = other.negative;

        other.digits = nullptr;
        other.size = 0;
        other.negative = false;
    }
    return *this;
}

void BigInt::resize(size_t new_size) {
    if (new_size <= size) return;
    int* new_digits = new int[new_size];
    for (size_t i = 0; i < size; i++) new_digits[i] = digits[i];
    for (size_t i = size; i < new_size; i++) new_digits[i] = 0;
    delete[] digits;
    digits = new_digits;
    size = new_size;
}

void BigInt::remove_leading_zeros() {
    while (size > 1 && digits[size - 1] == 0) {
        size--;
    }
    if (size == 1 && digits[0] == 0) {
        negative = false;
    }
}

int BigInt::compare_absolute(const BigInt& a, const BigInt& b) {
    if (a.size != b.size) {
        return (a.size > b.size) ? 1 : -1;
    }
    for (size_t i = a.size; i > 0; i--) {
        if (a.digits[i - 1] != b.digits[i - 1]) {
            return (a.digits[i - 1] > b.digits[i - 1]) ? 1 : -1;
        }
    }
    return 0;
}

BigInt BigInt::add_absolute(const BigInt& a, const BigInt& b) {
    BigInt result;
    size_t max_size = std::max(a.size, b.size);
    result.resize(max_size + 1);

    int carry = 0;
    for (size_t i = 0; i < max_size || carry; i++) {
        if (i >= result.size) result.resize(i + 1);
        int sum = carry;
        if (i < a.size) sum += a.digits[i];
        if (i < b.size) sum += b.digits[i];
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }

    result.remove_leading_zeros();
    return result;
}

BigInt BigInt::subtract_absolute(const BigInt& a, const BigInt& b) {
    BigInt result;
    result.resize(a.size);

    int borrow = 0;
    for (size_t i = 0; i < a.size; i++) {
        int diff = a.digits[i] - borrow;
        if (i < b.size) diff -= b.digits[i];

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = diff;
    }

    result.remove_leading_zeros();
    return result;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (negative == other.negative) {
        BigInt result = add_absolute(*this, other);
        result.negative = negative;
        return result;
    } else {
        int cmp = compare_absolute(*this, other);
        if (cmp == 0) {
            return BigInt(0);
        } else if (cmp > 0) {
            BigInt result = subtract_absolute(*this, other);
            result.negative = negative;
            return result;
        } else {
            BigInt result = subtract_absolute(other, *this);
            result.negative = other.negative;
            return result;
        }
    }
}

BigInt BigInt::operator+(int32_t value) const {
    return *this + BigInt(value);
}

BigInt BigInt::operator-(const BigInt& other) const {
    return *this + (-other);
}

BigInt BigInt::operator-(int32_t value) const {
    return *this - BigInt(value);
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.resize(size + other.size);
    result.negative = (negative != other.negative);

    for (size_t i = 0; i < size; i++) {
        int carry = 0;
        for (size_t j = 0; j < other.size || carry; j++) {
            size_t idx = i + j;
            if (idx >= result.size) result.resize(idx + 1);
            long long current = result.digits[idx] +
                               static_cast<long long>(digits[i]) * (j < other.size ? other.digits[j] : 0) + carry;
            result.digits[idx] = static_cast<int>(current % 10);
            carry = static_cast<int>(current / 10);
        }
    }

    result.remove_leading_zeros();
    return result;
}

BigInt BigInt::operator*(int32_t value) const {
    return *this * BigInt(value);
}

BigInt BigInt::operator-() const {
    BigInt result(*this);
    if (!(size == 1 && digits[0] == 0)) {
        result.negative = !negative;
    }
    return result;
}

bool BigInt::operator==(const BigInt& other) const {
    if (negative != other.negative || size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (negative != other.negative) {
        return negative;
    }

    int cmp = compare_absolute(*this, other);
    return negative ? (cmp > 0) : (cmp < 0);
}

bool BigInt::operator<=(const BigInt& other) const {
    return (*this < other) || (*this == other);
}

bool BigInt::operator>(const BigInt& other) const {
    return !(*this <= other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    if (num.negative) {
        os << '-';
    }
    for (size_t i = num.size; i > 0; i--) {
        os << num.digits[i - 1];
    }
    return os;
}
