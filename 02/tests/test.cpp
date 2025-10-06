#include <gtest/gtest.h>
#include "../src/allocator.h"
#include <iostream>

TEST(AllocatorTest, Initialization) {
    Allocator* alloc = init_allocator(static_cast<size_t>(100));
    EXPECT_NE(alloc, nullptr);
    EXPECT_NE(alloc->start, nullptr);
    EXPECT_EQ(alloc->end - alloc->start, 100);
    EXPECT_EQ(alloc->offset, static_cast<size_t>(0));
    clear(alloc);
}

TEST(AllocatorTest, Allocation) {
    Allocator* alloc2 = init_allocator(static_cast<size_t>(10));
    char* ptr1 = alloc(alloc2, 10);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_EQ(alloc2->offset, static_cast<size_t>(10));

    char* ptr2 = alloc(alloc2, 99);
    EXPECT_EQ(ptr2, nullptr);

    clear(alloc2);
}

TEST(AllocatorTest, Reset) {
    Allocator* alloc3 = init_allocator(static_cast<size_t>(10));

    char* ptr1 = alloc(alloc3, 5);
    EXPECT_EQ(alloc3->offset, static_cast<size_t>(5));
    EXPECT_NE(ptr1, nullptr);

    reset(alloc3);

    EXPECT_EQ(alloc3->offset, static_cast<size_t>(0));

    clear(alloc3);
}