#ifndef BST_MAP_HPP
#define BST_MAP_HPP

#include <memory>
#include <functional>
#include <utility>
#include <stdexcept>
#include <cstddef>
#include <iterator>

namespace bst_ns {

template <class T>
struct bst_allocator {
    using value_type = T;

    value_type* allocate(std::size_t n) {
        return static_cast<value_type*>(::operator new(n * sizeof(value_type)));
    }

    void deallocate(value_type* p, std::size_t) {
        ::operator delete(p);
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

    bool operator==(const bst_allocator&) const noexcept { return true; }
    bool operator!=(const bst_allocator&) const noexcept { return false; }
};

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = bst_allocator<std::pair<const Key, T>>
>
class bst {
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using key_compare = Compare;
    using allocator_type = Allocator;

private:
    struct Node {
        std::pair<const Key, T>* value;
        Node* left;
        Node* right;
        Node* parent;

        Node(const std::pair<const Key, T>& val, Node* p = nullptr)
            : value(nullptr), left(nullptr), right(nullptr), parent(p) {}
        ~Node() {}
    };

    using node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    using value_allocator = Allocator;

    Node* root_;
    size_type size_;
    Compare comp_;
    node_allocator node_alloc_;
    value_allocator value_alloc_;

public:
    class iterator {
    private:
        Node* cur_;
        const bst* tree_;

        static Node* minimum(Node* node) {
            while (node && node->left) node = node->left;
            return node;
        }

        static Node* maximum(Node* node) {
            while (node && node->right) node = node->right;
            return node;
        }

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<const Key, T>;
        using pointer = value_type*;
        using reference = value_type&;

        iterator() : cur_(nullptr), tree_(nullptr) {}
        iterator(Node* node, const bst* tree) : cur_(node), tree_(tree) {}

        bool operator==(const iterator& o) const noexcept { return cur_ == o.cur_; }
        bool operator!=(const iterator& o) const noexcept { return cur_ != o.cur_; }

        reference operator*() const { return *cur_->value; }
        pointer operator->() const { return cur_->value; }

        iterator& operator++() {
            if (!cur_) return *this;
            if (cur_->right) {
                cur_ = minimum(cur_->right);
            } else {
                Node* p = cur_->parent;
                while (p && cur_ == p->right) {
                    cur_ = p;
                    p = p->parent;
                }
                cur_ = p;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--() {
            if (!cur_) {
                cur_ = maximum(tree_->root_);
                return *this;
            }
            if (cur_->left) {
                cur_ = maximum(cur_->left);
            } else {
                Node* p = cur_->parent;
                while (p && cur_ == p->left) {
                    cur_ = p;
                    p = p->parent;
                }
                cur_ = p;
            }
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        friend class bst;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;

    bst() : root_(nullptr), size_(0), comp_(), node_alloc_(), value_alloc_() {}

    ~bst() {
        clear();
    }

    bst(const bst& other) : root_(nullptr), size_(0), comp_(other.comp_),
                             node_alloc_(other.node_alloc_), value_alloc_(other.value_alloc_) {
        for (auto it = other.cbegin(); it != other.cend(); ++it) {
            insert(*it);
        }
    }

    bst& operator=(const bst& other) {
        if (this != &other) {
            clear();
            comp_ = other.comp_;
            for (auto it = other.cbegin(); it != other.cend(); ++it) {
                insert(*it);
            }
        }
        return *this;
    }

    mapped_type& operator[](const key_type& key) {
        Node* node = find_node(key);
        if (node) {
            return node->value->second;
        }
        auto result = insert(std::make_pair(key, T()));
        return result.first->second;
    }

    mapped_type& at(const key_type& key) {
        Node* node = find_node(key);
        if (!node) {
            throw std::out_of_range("Key not found");
        }
        return node->value->second;
    }

    const mapped_type& at(const key_type& key) const {
        Node* node = find_node(key);
        if (!node) {
            throw std::out_of_range("Key not found");
        }
        return node->value->second;
    }

    std::pair<iterator, bool> insert(const value_type& value) {
        if (!root_) {
            root_ = create_node(value, nullptr);
            size_++;
            return {iterator(root_, this), true};
        }

        Node* current = root_;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (comp_(value.first, current->value->first)) {
                current = current->left;
            } else if (comp_(current->value->first, value.first)) {
                current = current->right;
            } else {
                return {iterator(current, this), false};
            }
        }

        Node* new_node = create_node(value, parent);
        if (comp_(value.first, parent->value->first)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        size_++;
        return {iterator(new_node, this), true};
    }

    size_type erase(const key_type& key) {
        Node* node = find_node(key);
        if (!node) return 0;

        erase_node(node);
        size_--;
        return 1;
    }

    iterator find(const key_type& key) {
        Node* node = find_node(key);
        return node ? iterator(node, this) : end();
    }

    iterator find(const key_type& key) const {
        Node* node = find_node(key);
        return node ? iterator(node, this) : end();
    }

    bool contains(const key_type& key) const {
        return find_node(key) != nullptr;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    size_type size() const noexcept {
        return size_;
    }

    void clear() {
        clear_recursive(root_);
        root_ = nullptr;
        size_ = 0;
    }

    iterator begin() {
        if (!root_) return end();
        Node* node = root_;
        while (node->left) node = node->left;
        return iterator(node, this);
    }

    iterator begin() const {
        return cbegin();
    }

    iterator cbegin() const {
        if (!root_) return cend();
        Node* node = root_;
        while (node->left) node = node->left;
        return iterator(node, this);
    }

    iterator end() {
        return iterator(nullptr, this);
    }

    iterator end() const {
        return cend();
    }

    iterator cend() const {
        return iterator(nullptr, this);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

private:
    Node* create_node(const value_type& value, Node* parent) {
        Node* node = node_alloc_.allocate(1);
        node->value = value_alloc_.allocate(1);
        value_alloc_.construct(node->value, value);
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
        return node;
    }

    void destroy_node(Node* node) {
        if (node) {
            if (node->value) {
                value_alloc_.destroy(node->value);
                value_alloc_.deallocate(node->value, 1);
            }
            node_alloc_.deallocate(node, 1);
        }
    }

    Node* find_node(const key_type& key) const {
        Node* current = root_;
        while (current) {
            if (comp_(key, current->value->first)) {
                current = current->left;
            } else if (comp_(current->value->first, key)) {
                current = current->right;
            } else {
                return current;
            }
        }
        return nullptr;
    }

    void erase_node(Node* node) {
        if (!node->left && !node->right) {
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            } else {
                root_ = nullptr;
            }
            destroy_node(node);
        } else if (!node->left || !node->right) {
            Node* child = node->left ? node->left : node->right;
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = child;
                else
                    node->parent->right = child;
                child->parent = node->parent;
            } else {
                root_ = child;
                child->parent = nullptr;
            }
            destroy_node(node);
        } else {
            Node* successor = node->right;
            while (successor->left) successor = successor->left;

            value_alloc_.destroy(node->value);
            value_alloc_.construct(node->value, *successor->value);

            erase_node(successor);
            size_++;
        }
    }

    void clear_recursive(Node* node) {
        if (node) {
            clear_recursive(node->left);
            clear_recursive(node->right);
            destroy_node(node);
        }
    }
};

} // namespace bst_ns

#endif // BST_MAP_HPP