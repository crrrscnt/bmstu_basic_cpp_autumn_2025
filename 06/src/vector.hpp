#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>
#include <initializer_list>

template<typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Vector(size_t n) : data_(n ? new T[n] : nullptr), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) data_[i] = T();
    }

    Vector(size_t n, const T& value) : data_(n ? new T[n] : nullptr), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) data_[i] = value;
    }

    Vector(const Vector& other) : data_(other.capacity_ ? new T[other.capacity_] : nullptr),
                                  size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        T* new_data = other.capacity_ ? new T[other.capacity_] : nullptr;
        for (size_t i = 0; i < other.size_; ++i) new_data[i] = other.data_[i];
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }

    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    ~Vector() { delete[] data_; }

    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    T& front() {
        if (empty()) throw std::out_of_range("front on empty");
        return data_[0];
    }
    const T& front() const {
        if (empty()) throw std::out_of_range("front on empty");
        return data_[0];
    }

    T& back() {
        if (empty()) throw std::out_of_range("back on empty");
        return data_[size_ - 1];
    }
    const T& back() const {
        if (empty()) throw std::out_of_range("back on empty");
        return data_[size_ - 1];
    }

    T* data() { return data_; }
    const T* data() const { return data_; }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    size_t max_size() const { return std::numeric_limits<size_t>::max() / sizeof(T); }

    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) return;
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    size_t capacity() const { return capacity_; }

    void shrink_to_fit() {
        if (size_ == capacity_) return;
        size_t new_cap = size_ ? size_ : 0;
        T* new_data = new_cap ? new T[new_cap] : nullptr;
        for (size_t i = 0; i < size_; ++i) new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ ? capacity_ * 2 : 1;
            reserve(new_cap);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ ? capacity_ * 2 : 1;
            reserve(new_cap);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("pop_back on empty");
        --size_;
    }

    void insert(size_t pos, const T& value) {
        if (pos > size_) throw std::out_of_range("insert");
        if (size_ == capacity_) {
            size_t new_cap = capacity_ ? capacity_ * 2 : 1;
            T* new_data = new T[new_cap];
            for (size_t i = 0; i < pos; ++i) new_data[i] = std::move(data_[i]);
            new_data[pos] = value;
            for (size_t i = pos; i < size_; ++i) new_data[i + 1] = std::move(data_[i]);
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
            ++size_;
        } else {
            for (size_t i = size_; i > pos; --i) data_[i] = std::move(data_[i - 1]);
            data_[pos] = value;
            ++size_;
        }
    }

    template<typename... Args>
    void emplace(size_t pos, Args&&... args) {
        if (pos > size_) throw std::out_of_range("");
        if (size_ == capacity_) {
            size_t new_cap = capacity_ * 2;
            T* new_data = new T[new_cap];
            for (size_t i = 0; i < pos; ++i) new_data[i] = std::move(data_[i]);
            new_data[pos] = T(std::forward<Args>(args)...);
            for (size_t i = pos; i < size_; ++i) new_data[i + 1] = std::move(data_[i]);
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
            ++size_;
        } else {
            for (size_t i = size_; i > pos; --i) data_[i] = std::move(data_[i - 1]);
            data_[pos] = T(std::forward<Args>(args)...);
            ++size_;
        }
    }

    void resize(size_t new_size) {
        if (new_size > capacity_) reserve(new_size);
        for (size_t i = size_; i < new_size; ++i) data_[i] = T();
        size_ = new_size;
    }

    void resize(size_t new_size, const T& value) {
        if (new_size > capacity_) reserve(new_size);
        for (size_t i = size_; i < new_size; ++i) data_[i] = value;
        size_ = new_size;
    }

    void reverse() {
        for (size_t i = 0, j = (size_ ? size_ - 1 : 0); i < j; ++i, --j) std::swap(data_[i], data_[j]);
    }

    void clear() { size_ = 0; }
};

// spec for bool
template<>
class Vector<bool> {
private:
    unsigned char* data_;
    size_t size_;
    size_t capacity_;
    static constexpr size_t BITS_PER_BYTE = 8;

    size_t bytes_for_bits(size_t bits) const { return (bits + BITS_PER_BYTE - 1) / BITS_PER_BYTE; }

public:
    class Reference {
    private:
        unsigned char& byte_;
        size_t bit_idx_;
    public:
        Reference(unsigned char& b, size_t idx) : byte_(b), bit_idx_(idx) {}
        Reference& operator=(bool v) {
            if (v) byte_ |= static_cast<unsigned char>(1u << bit_idx_);
            else byte_ &= static_cast<unsigned char>(~(1u << bit_idx_));
            return *this;
        }
        Reference& operator=(const Reference& r) { return *this = bool(r); }
        operator bool() const { return (byte_ & static_cast<unsigned char>(1u << bit_idx_)) != 0; }
    };

    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Vector(size_t n) : data_(n ? new unsigned char[bytes_for_bits(n)]() : nullptr), size_(n), capacity_(n) {}

    Vector(size_t n, bool value) : data_(n ? new unsigned char[bytes_for_bits(n)]() : nullptr), size_(n), capacity_(n) {
        if (value) for (size_t i = 0; i < n; ++i) (*this)[i] = true;
    }

    Vector(const Vector& other) : data_(other.capacity_ ? new unsigned char[bytes_for_bits(other.capacity_)]() : nullptr),
                                  size_(other.size_), capacity_(other.capacity_) {
        if (data_) {
            size_t bytes = bytes_for_bits(size_);
            for (size_t i = 0; i < bytes; ++i) data_[i] = other.data_[i];
        }
    }

    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr; other.size_ = 0; other.capacity_ = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.capacity_ ? new unsigned char[bytes_for_bits(other.capacity_)]() : nullptr;
        size_ = other.size_;
        capacity_ = other.capacity_;
        if (data_) {
            size_t bytes = bytes_for_bits(size_);
            for (size_t i = 0; i < bytes; ++i) data_[i] = other.data_[i];
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr; other.size_ = 0; other.capacity_ = 0;
        return *this;
    }

    ~Vector() { delete[] data_; }

    Reference operator[](size_t index) {
        size_t b = index / BITS_PER_BYTE;
        size_t bit = index % BITS_PER_BYTE;
        return Reference(data_[b], bit);
    }
    bool operator[](size_t index) const {
        size_t b = index / BITS_PER_BYTE;
        size_t bit = index % BITS_PER_BYTE;
        return (data_[b] & static_cast<unsigned char>(1u << bit)) != 0;
    }

    Reference front() { if (size_ == 0) throw std::out_of_range("front"); return (*this)[0]; }
    bool front() const { if (size_ == 0) throw std::out_of_range("front"); return (*this)[0]; }
    Reference back() { if (size_ == 0) throw std::out_of_range("back"); return (*this)[size_ - 1]; }
    bool back() const { if (size_ == 0) throw std::out_of_range("back"); return (*this)[size_ - 1]; }

    unsigned char* data() { return data_; }
    const unsigned char* data() const { return data_; }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    size_t max_size() const { return std::numeric_limits<size_t>::max() * BITS_PER_BYTE; }

    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) return;
        size_t new_bytes = bytes_for_bits(new_cap);
        unsigned char* new_data = new unsigned char[new_bytes]();
        if (data_) {
            size_t old_bytes = bytes_for_bits(size_);
            for (size_t i = 0; i < old_bytes; ++i) new_data[i] = data_[i];
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_cap;
    }

    size_t capacity() const { return capacity_; }

    void shrink_to_fit() {
        if (capacity_ == size_) return;
        size_t new_bytes = bytes_for_bits(size_);
        unsigned char* new_data = new_bytes ? new unsigned char[new_bytes]() : nullptr;
        if (data_ && new_data) {
            for (size_t i = 0; i < new_bytes; ++i) new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }

    void push_back(bool value) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ ? capacity_ * 2 : 1;
            reserve(new_cap);
        }
        (*this)[size_] = value;
        ++size_;
    }

    void pop_back() { if (empty()) throw std::out_of_range("pop_back"); --size_; }

    void insert(size_t pos, bool value) {
        if (pos > size_) throw std::out_of_range("insert");
        if (size_ == capacity_) reserve(capacity_ ? capacity_ * 2 : 1);
        for (size_t i = size_; i > pos; --i) (*this)[i] = (*this)[i - 1];
        (*this)[pos] = value;
        ++size_;
    }

    void emplace(size_t pos, bool value) { insert(pos, value); }

    void resize(size_t count) {
        if (count > capacity_) reserve(count);
        size_ = count;
    }

    void resize(size_t count, bool value) {
        size_t old = size_;
        resize(count);
        if (count > old && value) {
            for (size_t i = old; i < count; ++i) (*this)[i] = true;
        }
    }

    void reverse() {
        for (size_t i = 0; i < size_ / 2; ++i) {
            bool t = (*this)[i];
            (*this)[i] = (*this)[size_ - 1 - i];
            (*this)[size_ - 1 - i] = t;
        }
    }

    void clear() { size_ = 0; }
};

#endif // VECTOR_HPP
