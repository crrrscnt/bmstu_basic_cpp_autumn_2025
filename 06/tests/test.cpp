#include <gtest/gtest.h>
#include "../src/vector.hpp"
#include <string>

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor) {
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_GE(v.capacity(), 5u);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(VectorTest, SizeValueConstructor) {
    Vector<int> v(5, 42);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 42);
    }
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> v1;
    v1.push_back(1); v1.push_back(2); v1.push_back(3);
    Vector<int> v2(v1);

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);

    v2[0] = 10;
    EXPECT_EQ(v1[0], 1);
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> v1;
    v1.push_back(1); v1.push_back(2); v1.push_back(3);
    Vector<int> v2(std::move(v1));

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v1.size(), 0u);
}

TEST(VectorTest, OperatorBrackets) {
    Vector<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);

    v[1] = 25;
    EXPECT_EQ(v[1], 25);
}

TEST(VectorTest, Front) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    EXPECT_EQ(v.front(), 1);

    v.front() = 10;
    EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, FrontEmpty) {
    Vector<int> v;
    EXPECT_THROW(v.front(), std::out_of_range);
}

TEST(VectorTest, Back) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    EXPECT_EQ(v.back(), 3);

    v.back() = 30;
    EXPECT_EQ(v[2], 30);
}

TEST(VectorTest, Data) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    int* ptr = v.data();
    EXPECT_EQ(ptr[0], 1);
    EXPECT_EQ(ptr[1], 2);
    EXPECT_EQ(ptr[2], 3);
}

TEST(VectorTest, Empty) {
    Vector<int> v;
    EXPECT_TRUE(v.empty());

    v.push_back(1);
    EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);

    v.push_back(1);
    EXPECT_EQ(v.size(), 1u);

    v.push_back(2);
    EXPECT_EQ(v.size(), 2u);
}

TEST(VectorTest, Reserve) {
    Vector<int> v;
    v.reserve(10);
    EXPECT_GE(v.capacity(), 10u);
    EXPECT_EQ(v.size(), 0u);
}

TEST(VectorTest, CapacityGrowthOnPush) {
    Vector<int> v;
    size_t initial_cap = v.capacity();

    v.push_back(1);
    EXPECT_GT(v.capacity(), initial_cap);
}

TEST(VectorTest, ShrinkToFit) {
    Vector<int> v;
    v.reserve(100);
    v.push_back(1);
    v.push_back(2);

    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
}

TEST(VectorTest, PushBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PushBackRvalue) {
    Vector<std::string> v;
    v.push_back(std::string("hello"));
    EXPECT_EQ(v[0], "hello");
}

TEST(VectorTest, PopBack) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    v.pop_back();

    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, PopBackEmpty) {
    Vector<int> v;
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(VectorTest, Insert) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(4);
    v.insert(2, 3);

    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, InsertAtBeginning) {
    Vector<int> v;
    v.push_back(2); v.push_back(3);
    v.insert(0, 1);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertAtEnd) {
    Vector<int> v;
    v.push_back(1); v.push_back(2);
    v.insert(2, 3);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertOutOfRange) {
    Vector<int> v;
    v.push_back(1); v.push_back(2);
    EXPECT_THROW(v.insert(10, 3), std::out_of_range);
}

TEST(VectorTest, Emplace) {
    Vector<std::string> v;
    v.push_back(std::string("hello"));
    v.push_back(std::string("world"));
    v.emplace(1, 5, 'x'); // "xxxxx" на 1

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v[1], "xxxxx");
    EXPECT_EQ(v[2], "world");
}

TEST(VectorTest, Resize) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    v.resize(5);

    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[3], 0);
    EXPECT_EQ(v[4], 0);
}


TEST(VectorTest, ResizeWithValue) {
    Vector<int> v;
    v.push_back(1); v.push_back(2);
    v.resize(5, 42);

    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[2], 42);
    EXPECT_EQ(v[3], 42);
    EXPECT_EQ(v[4], 42);
}

TEST(VectorTest, Reverse) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4); v.push_back(5);
    v.reverse();

    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v[1], 4);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 2);
    EXPECT_EQ(v[4], 1);
}

TEST(VectorTest, ReverseEvenSize) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);
    v.reverse();

    EXPECT_EQ(v[0], 4);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 1);
}

TEST(VectorTest, Clear) {
    Vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    v.clear();

    EXPECT_EQ(v.size(), 0u);
    EXPECT_TRUE(v.empty());
}

// bool
TEST(VectorBoolTest, DefaultConstructor) {
    Vector<bool> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_TRUE(v.empty());
}

TEST(VectorBoolTest, SizeConstructor) {
    Vector<bool> v(10);
    EXPECT_EQ(v.size(), 10u);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_FALSE(v[i]);
    }
}

TEST(VectorBoolTest, SizeValueConstructor) {
    Vector<bool> v(10, true);
    EXPECT_EQ(v.size(), 10u);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_TRUE(v[i]);
    }
}

TEST(VectorBoolTest, CopyConstructor) {
    Vector<bool> v1;
    v1.push_back(true); v1.push_back(false); v1.push_back(true);
    Vector<bool> v2(v1);

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_TRUE(v2[0]);
    EXPECT_FALSE(v2[1]);
    EXPECT_TRUE(v2[2]);
}

TEST(VectorBoolTest, MoveConstructor) {
    Vector<bool> v1;
    v1.push_back(true); v1.push_back(false); v1.push_back(true);
    Vector<bool> v2(std::move(v1));

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_TRUE(v2[0]);
    EXPECT_EQ(v1.size(), 0u);
}

TEST(VectorBoolTest, CopyAssignment) {
    Vector<bool> v1;
    v1.push_back(true); v1.push_back(false); v1.push_back(true);
    Vector<bool> v2;
    v2 = v1;

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_TRUE(v2[0]);
    EXPECT_FALSE(v2[1]);
}

TEST(VectorBoolTest, MoveAssignment) {
    Vector<bool> v1;
    v1.push_back(true); v1.push_back(false); v1.push_back(true);
    Vector<bool> v2;
    v2 = std::move(v1);

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_TRUE(v2[0]);
    EXPECT_EQ(v1.size(), 0u);
}

TEST(VectorBoolTest, Front) {
    Vector<bool> v;
    v.push_back(true); v.push_back(false);
    EXPECT_TRUE(v.front());

    v.front() = false;
    EXPECT_FALSE(v[0]);
}

TEST(VectorBoolTest, Back) {
    Vector<bool> v;
    v.push_back(false); v.push_back(true);
    EXPECT_TRUE(v.back());

    v.back() = false;
    EXPECT_FALSE(v[1]);
}

TEST(VectorBoolTest, PushBack) {
    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);

    EXPECT_EQ(v.size(), 3u);
    EXPECT_TRUE(v[0]);
    EXPECT_FALSE(v[1]);
    EXPECT_TRUE(v[2]);
}

TEST(VectorBoolTest, PushBackMany) {
    Vector<bool> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i % 2 == 0);
    }

    EXPECT_EQ(v.size(), 100u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(v[i], i % 2 == 0);
    }
}

TEST(VectorBoolTest, PopBack) {
    Vector<bool> v;
    v.push_back(true); v.push_back(false); v.push_back(true);
    v.pop_back();

    EXPECT_EQ(v.size(), 2u);
    EXPECT_TRUE(v[0]);
    EXPECT_FALSE(v[1]);
}

TEST(VectorBoolTest, Insert) {
    Vector<bool> v;
    v.push_back(true); v.push_back(false); v.push_back(false);
    v.insert(1, true);

    EXPECT_EQ(v.size(), 4u);
    EXPECT_TRUE(v[0]);
    EXPECT_TRUE(v[1]);
    EXPECT_FALSE(v[2]);
    EXPECT_FALSE(v[3]);
}

TEST(VectorBoolTest, Resize) {
    Vector<bool> v;
    v.push_back(true); v.push_back(false);
    v.resize(5);

    EXPECT_EQ(v.size(), 5u);
    EXPECT_TRUE(v[0]);
    EXPECT_FALSE(v[1]);
    EXPECT_FALSE(v[2]);
}

TEST(VectorBoolTest, ResizeWithValue) {
    Vector<bool> v;
    v.push_back(true); v.push_back(false);
    v.resize(5, true);

    EXPECT_EQ(v.size(), 5u);
    EXPECT_TRUE(v[2]);
    EXPECT_TRUE(v[3]);
    EXPECT_TRUE(v[4]);
}

TEST(VectorBoolTest, Reverse) {
    Vector<bool> v;
    v.push_back(true); v.push_back(false); v.push_back(true); v.push_back(false); v.push_back(true);
    v.reverse();

    EXPECT_TRUE(v[0]);
    EXPECT_FALSE(v[1]);
    EXPECT_TRUE(v[2]);
    EXPECT_FALSE(v[3]);
    EXPECT_TRUE(v[4]);
}

TEST(VectorBoolTest, Clear) {
    Vector<bool> v;
    v.push_back(true); v.push_back(false); v.push_back(true);
    v.clear();

    EXPECT_EQ(v.size(), 0u);
    EXPECT_TRUE(v.empty());
}

TEST(VectorBoolTest, Reserve) {
    Vector<bool> v;
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100u);
}

TEST(VectorBoolTest, ShrinkToFit) {
    Vector<bool> v;
    v.reserve(100);
    v.push_back(true);
    v.push_back(false);

    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
}
