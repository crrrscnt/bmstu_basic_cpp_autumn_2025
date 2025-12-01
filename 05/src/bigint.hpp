#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

class BigInt {
private:
    int* digits;
    size_t size;
    bool negative;

    void resize(size_t new_size);
    void remove_leading_zeros();
    void copy_from(const BigInt& other);

    static BigInt add_absolute(const BigInt& a, const BigInt& b);
    static BigInt subtract_absolute(const BigInt& a, const BigInt& b);
    static int compare_absolute(const BigInt& a, const BigInt& b);

public:
    BigInt();
    BigInt(int32_t value);
    BigInt(const std::string& str);
    BigInt(const BigInt& other);
    BigInt(BigInt&& other) noexcept;

    ~BigInt();

    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other) noexcept;
    BigInt operator+(const BigInt& other) const;
    BigInt operator+(int32_t value) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator-(int32_t value) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator*(int32_t value) const;
    BigInt operator-() const;

    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
};

#endif // BIGINT_HPP