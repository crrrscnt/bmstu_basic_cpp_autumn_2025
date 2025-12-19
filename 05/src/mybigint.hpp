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
    void removeLeadingZeros();

    static BigInt addAbsolute(const BigInt& a, const BigInt& b);
    static BigInt subtractAbsolute(const BigInt& a, const BigInt& b);
    static int compareAbsolute(const BigInt& a, const BigInt& b);

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
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator-() const;

    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    friend void swap(BigInt& first, BigInt& second);
};

#endif // BIGINT_HPP