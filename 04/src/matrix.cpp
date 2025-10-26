#include "matrix.hpp"

// ProxyRow

Matrix::ProxyRow::ProxyRow(int32_t *data_, size_t col_)
    : data_(data_), col_(col_) {}

int32_t& Matrix::ProxyRow::operator[](size_t j)
{
    if (j >= col_)
    {
        throw std::out_of_range("");
    }
    return data_[j];
}

// Matrix

Matrix::Matrix(size_t rows_, size_t columns_)
    : rows_(rows_), columns_(columns_) {
    if (rows_ <= 0 || columns_ <= 0)
    {
        throw std::invalid_argument("");
    }
    data_ = new int32_t[rows_ * columns_]();
    rows_data_ = new ProxyRow* [rows_];
    for (size_t i = 0; i < rows_; ++i)
    {
        rows_data_[i] = new ProxyRow(data_ + i * columns_, columns_);
    }
}

Matrix::~Matrix() {
    delete[] rows_data_;
    delete[] data_;
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), columns_(other.columns_){
    data_ = new int32_t[rows_ * columns_];
    for (size_t i = 0; i < rows_ * columns_; ++i)
    {
        data_[i] = other.data_[i];
    }

    rows_data_ = new ProxyRow* [rows_];
    for (size_t row = 0; row < rows_; ++row) {
        rows_data_[row] = new ProxyRow(data_ + row * columns_, columns_);
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other)
    {
        return *this;
    }

    delete[] rows_data_;
    delete[] data_;

    rows_ = other.rows_;
    columns_ = other.columns_;

    data_ = new int32_t[rows_ * columns_];
    rows_data_ = new ProxyRow*[rows_];

    for (size_t i = 0; i < rows_ * columns_; ++i)
    {
        data_[i] = other.data_[i];
    }

    for (size_t i = 0; i < rows_; ++i)
    {
        rows_data_[i] = new ProxyRow(data_ + i * columns_, columns_);
    }

    return *this;
}

size_t Matrix::getNumRows() const {
    return rows_;
};

size_t Matrix::getNumCol() const {
    return columns_;
}

Matrix& Matrix::operator*=(int32_t num) {
    for (size_t i = 0; i < rows_ * columns_; ++i)
    {
        data_[i] *= num;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
    Matrix result(rows_, columns_);
    for (size_t i = 0; i < rows_ * columns_; ++i)
    {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows_ != other.rows_ || columns_ != other.columns_) {
        return false;
    }
    for (size_t i = 0; i < rows_ * columns_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    if (rows_ != other.rows_ || columns_ != other.columns_) {
        return true;
    }
    for (size_t i = 0; i < rows_ * columns_; ++i) {
        if (data_[i] != other.data_[i]) {
            return true;
        }
    }
    return false;
}

Matrix::ProxyRow& Matrix::operator[](size_t i) {
    if (i >= rows_) {
        throw std::out_of_range("");
    }
    return *rows_data_[i];
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    for (size_t i = 0; i < m.rows_; ++i) {
        for (size_t j = 0; j < m.columns_; ++j) {
            out << m.data_[i * m.columns_ + j];
            if (j < m.columns_ - 1) {
                out << " ";
            }
        }
        if (i < m.rows_ - 1) {
            out << "\n";
        }
    }
    return out;
}