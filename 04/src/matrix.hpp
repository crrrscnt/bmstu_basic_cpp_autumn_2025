#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <stdexcept>
#include <iostream>

class Matrix {
    class ProxyRow
    {
    private:
        int32_t *data_;
        size_t col_;
    public:
        ProxyRow(int32_t *data_, size_t col);
        int32_t& operator[](size_t j);
    };
public:
    Matrix(size_t rows_, size_t columns_);
    ~Matrix();
    Matrix(const Matrix& other);

    size_t getNumRows() const;
    size_t getNumCol() const;

    Matrix& operator=(const Matrix& other);
    Matrix& operator*=(int32_t num);
    Matrix operator+(const Matrix& other);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    ProxyRow& operator[](size_t i);

    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
private:
    ProxyRow **rows_data_;
    int32_t *data_;
    size_t rows_;
    size_t columns_;
};

#endif // MATRIX_H