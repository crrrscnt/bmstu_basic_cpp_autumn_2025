#include <gtest/gtest.h>
#include "../src/matrix.hpp"

TEST(MatrixTest, InitAndGetColRows) {
    ASSERT_THROW(Matrix m0(static_cast<size_t>(0), static_cast<size_t>(-5));, std::invalid_argument);

    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);
    ASSERT_EQ(m.getNumRows(), static_cast<size_t>(5));
    ASSERT_EQ(m.getNumCol(), static_cast<size_t>(3));
}

TEST(MatrixTest, CopyConstructor) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix m2(m1);

    ASSERT_EQ(m2[0][0], 1);
    ASSERT_EQ(m2[0][1], 2);
    ASSERT_EQ(m2[1][0], 3);
    ASSERT_EQ(m2[1][1], 4);

    m1[0][0] = 99;
    ASSERT_EQ(m2[0][0], 1);
}

TEST(MatrixTest, AssignmentOperator) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix m2(3, 3);
    m2 = m1;

    ASSERT_EQ(m2.getNumRows(), static_cast<size_t>(2));
    ASSERT_EQ(m2.getNumCol(), static_cast<size_t>(2));
    ASSERT_EQ(m2[0][0], 1);
    ASSERT_EQ(m2[1][1], 4);

    m1[0][0] = 99;
    ASSERT_EQ(m2[0][0], 1);
}

TEST(MatrixTest, ElementAccess) {
    Matrix m(5, 3);

    m[1][2] = 5;
    ASSERT_EQ(m[1][2], 5);

    m[4][1] = 42;
    int32_t x = m[4][1];
    ASSERT_EQ(x, 42);
}

TEST(MatrixTest, MultiplyByNum) {
    Matrix m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    m *= 3;

    ASSERT_EQ(m[0][0], 3);
    ASSERT_EQ(m[0][1], 6);
    ASSERT_EQ(m[1][0], 9);
    ASSERT_EQ(m[1][1], 12);
}

TEST(MatrixTest, MatrixAddition) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix m2(2, 2);
    m2[0][0] = 5;
    m2[0][1] = 6;
    m2[1][0] = 7;
    m2[1][1] = 8;

    Matrix m3 = m1 + m2;

    ASSERT_EQ(m3[0][0], 6);
    ASSERT_EQ(m3[0][1], 8);
    ASSERT_EQ(m3[1][0], 10);
    ASSERT_EQ(m3[1][1], 12);
}

TEST(MatrixTest, Equality) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix m2(2, 2);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[1][0] = 3;
    m2[1][1] = 4;

    ASSERT_TRUE(m1 == m2);

    m2[1][1] = 5;
    ASSERT_FALSE(m1 == m2);
}

TEST(MatrixTest, Inequality) {
    Matrix m1(2, 2);
    m1[0][0] = 1;

    Matrix m2(2, 2);
    m2[0][0] = 2;

    ASSERT_TRUE(m1 != m2);

    m2[0][0] = 1;
    ASSERT_FALSE(m1 != m2);
}

TEST(MatrixTest, DifferentSizesNotEqual) {
    Matrix m1(2, 2);
    Matrix m2(3, 3);

    ASSERT_TRUE(m1 != m2);
}

TEST(MatrixTest, Output) {
    Matrix m(2, 3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;

    std::ostringstream oss;
    oss << m;

    ASSERT_EQ(oss.str(), "1 2 3\n4 5 6");
}

TEST(MatrixTest, OutOfRangeRow) {
    Matrix m(3, 3);

    ASSERT_THROW(m[5][0], std::out_of_range);
}

TEST(MatrixTest, OutOfRangeColumn) {
    Matrix m(3, 3);

    ASSERT_THROW(m[0][5], std::out_of_range);
}