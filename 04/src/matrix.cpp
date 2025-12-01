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

// Matrix::ProxyRow::ProxyRow(const ProxyRow& other)
//     : data_(new int32_t[other.col_]), col_(other.col_) {
//         std::copy(other.data_, other.data_ + col_, data_);
// }

// Matrix::ProxyRow& Matrix::ProxyRow::operator=(const ProxyRow& other) {
//     if (this != &other)
//     {
//         delete[] data_;
//         col_ = other.col_;
//         data_ = new int32_t[col_];
//         std::copy(other.data_, other.data_ + col_, data_);
//     }
//     return *this;
// }

// Matrix

Matrix::Matrix(size_t rows_, size_t columns_)
    : rows_(rows_), columns_(columns_) {
    if (rows_ <= 0 || columns_ <= 0)
    {
        throw std::invalid_argument("");
    }
    data_ = new int32_t[rows_ * columns_]();
}

Matrix::~Matrix() {
    delete[] data_;
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), columns_(other.columns_){
    data_ = new int32_t[rows_ * columns_];
    for (size_t i = 0; i < rows_ * columns_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

Matrix& Matrix::operator=(Matrix other) {
    if (this != &other)
    {
        Matrix temp(other);
        std::swap(rows_, temp.rows_);
        std::swap(columns_, temp.columns_);
        std::swap(data_, temp.data_);
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
    return !(*this == other);
}

Matrix::ProxyRow Matrix::operator[](size_t i) {
    if (i >= rows_) {
        throw std::out_of_range("");
    }
    return ProxyRow(data_ + i * columns_, columns_);
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