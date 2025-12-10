#include <gtest/gtest.h>
#include "../src/bin_tree.hpp"
#include <string>
#include <vector>

using namespace bst_ns;

TEST(BST, BasicInsertAndFind) {
    bst<int, std::string> tree;

    tree.insert({5, "five"});
    tree.insert({3, "three"});
    tree.insert({7, "seven"});
    tree.insert({1, "one"});
    tree.insert({9, "nine"});

    EXPECT_EQ(tree.size(), 5u);
    EXPECT_FALSE(tree.empty());
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_FALSE(tree.contains(10));

    auto it = tree.find(5);
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->first, 5);
    EXPECT_EQ(it->second, "five");
}

TEST(BST, OperatorBracket) {
    bst<int, std::string> tree;

    tree[10] = "ten";
    tree[5] = "five";
    tree[15] = "fifteen";

    EXPECT_EQ(tree.size(), 3u);
    EXPECT_EQ(tree[10], "ten");
    EXPECT_EQ(tree[5], "five");
    EXPECT_EQ(tree[15], "fifteen");

    tree[10] = "modified";
    EXPECT_EQ(tree[10], "modified");
    EXPECT_EQ(tree.size(), 3u);
}

TEST(BST, AtMethod) {
    bst<int, std::string> tree;

    tree.insert({1, "one"});
    tree.insert({2, "two"});

    EXPECT_EQ(tree.at(1), "one");
    EXPECT_EQ(tree.at(2), "two");
    EXPECT_THROW(tree.at(999), std::out_of_range);
}

TEST(BST, Erase) {
    bst<int, std::string> tree;

    tree.insert({5, "five"});
    tree.insert({3, "three"});
    tree.insert({7, "seven"});
    tree.insert({1, "one"});
    tree.insert({9, "nine"});
    tree.insert({6, "six"});
    tree.insert({8, "eight"});

    EXPECT_EQ(tree.size(), 7u);

    EXPECT_TRUE(tree.erase(1));
    EXPECT_EQ(tree.size(), 6u);
    EXPECT_FALSE(tree.contains(1));

    EXPECT_TRUE(tree.erase(9));
    EXPECT_EQ(tree.size(), 5u);
    EXPECT_FALSE(tree.contains(9));

    EXPECT_TRUE(tree.erase(7));
    EXPECT_EQ(tree.size(), 4u);
    EXPECT_FALSE(tree.contains(7));
    EXPECT_TRUE(tree.contains(8));

    EXPECT_FALSE(tree.erase(999));
    EXPECT_EQ(tree.size(), 4u);
}

TEST(BST, IteratorForward) {
    bst<int, std::string> tree;

    tree.insert({5, "five"});
    tree.insert({3, "three"});
    tree.insert({7, "seven"});
    tree.insert({1, "one"});
    tree.insert({9, "nine"});
    tree.insert({4, "four"});
    tree.insert({6, "six"});

    std::vector<int> expected = {1, 3, 4, 5, 6, 7, 9};
    std::vector<int> actual;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        actual.push_back(it->first);
    }
    EXPECT_EQ(actual, expected);

    actual.clear();
    for (const auto& pair : tree) {
        actual.push_back(pair.first);
    }
    EXPECT_EQ(actual, expected);
}

TEST(BST, IteratorBackward) {
    bst<int, std::string> tree;

    tree.insert({5, "five"});
    tree.insert({3, "three"});
    tree.insert({7, "seven"});
    tree.insert({1, "one"});
    tree.insert({9, "nine"});

    std::vector<int> expected = {9, 7, 5, 3, 1};
    std::vector<int> actual;

    auto it = tree.end();
    while (it != tree.begin()) {
        --it;
        actual.push_back(it->first);
    }
    EXPECT_EQ(actual, expected);
}

TEST(BST, ReverseIterator) {
    bst<int, std::string> tree;

    tree.insert({5, "five"});
    tree.insert({3, "three"});
    tree.insert({7, "seven"});
    tree.insert({1, "one"});
    tree.insert({9, "nine"});

    std::vector<int> expected = {9, 7, 5, 3, 1};
    std::vector<int> actual;

    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
        actual.push_back(it->first);
    }
    EXPECT_EQ(actual, expected);
}

TEST(BST, Clear) {
    bst<int, std::string> tree;

    tree.insert({1, "one"});
    tree.insert({2, "two"});
    tree.insert({3, "three"});

    EXPECT_EQ(tree.size(), 3u);
    EXPECT_FALSE(tree.empty());

    tree.clear();

    EXPECT_EQ(tree.size(), 0u);
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.find(1), tree.end());

    tree.insert({10, "ten"});
    EXPECT_EQ(tree.size(), 1u);
}

TEST(BST, CopyConstructor) {
    bst<int, std::string> tree1;

    tree1.insert({5, "five"});
    tree1.insert({3, "three"});
    tree1.insert({7, "seven"});

    bst<int, std::string> tree2(tree1);

    EXPECT_EQ(tree2.size(), 3u);
    EXPECT_TRUE(tree2.contains(5));
    EXPECT_TRUE(tree2.contains(3));
    EXPECT_TRUE(tree2.contains(7));
    EXPECT_EQ(tree2[5], "five");

    tree1.clear();
    EXPECT_EQ(tree2.size(), 3u);
}

TEST(BST, AssignmentOperator) {
    bst<int, std::string> tree1;

    tree1.insert({5, "five"});
    tree1.insert({3, "three"});

    bst<int, std::string> tree2;
    tree2.insert({10, "ten"});

    tree2 = tree1;

    EXPECT_EQ(tree2.size(), 2u);
    EXPECT_TRUE(tree2.contains(5));
    EXPECT_TRUE(tree2.contains(3));
    EXPECT_FALSE(tree2.contains(10));
}

TEST(BST, CustomComparator) {
    bst<int, std::string, std::greater<int>> tree;

    tree.insert({5, "five"});
    tree.insert({3, "three"});
    tree.insert({7, "seven"});
    tree.insert({1, "one"});
    tree.insert({9, "nine"});

    std::vector<int> expected = {9, 7, 5, 3, 1};
    std::vector<int> actual;

    for (const auto& pair : tree) {
        actual.push_back(pair.first);
    }
    EXPECT_EQ(actual, expected);
}

TEST(BST, StringKeys) {
    bst<std::string, int> tree;

    tree["apple"] = 1;
    tree["banana"] = 2;
    tree["cherry"] = 3;
    tree["date"] = 4;

    EXPECT_EQ(tree.size(), 4u);
    EXPECT_EQ(tree["apple"], 1);
    EXPECT_EQ(tree["banana"], 2);
    EXPECT_TRUE(tree.contains("cherry"));
    EXPECT_FALSE(tree.contains("elderberry"));

    std::vector<std::string> expected = {"apple", "banana", "cherry", "date"};
    std::vector<std::string> actual;

    for (const auto& pair : tree) {
        actual.push_back(pair.first);
    }
    EXPECT_EQ(actual, expected);
}

TEST(BST, LargeTree) {
    bst<int, int> tree;

    const int N = 1000;
    for (int i = 0; i < N; ++i) tree.insert({i, i * 2});

    EXPECT_EQ(tree.size(), static_cast<std::size_t>(N));

    for (int i = 0; i < N; ++i) {
        EXPECT_TRUE(tree.contains(i));
        EXPECT_EQ(tree[i], i * 2);
    }

    for (int i = 0; i < N; i += 2) tree.erase(i);

    EXPECT_EQ(tree.size(), static_cast<std::size_t>(N / 2));

    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0) EXPECT_FALSE(tree.contains(i));
        else EXPECT_TRUE(tree.contains(i));
    }
}