#include <gtest/gtest.h>

#include "ADT/Matrix.h"

class Matrix_test : public ::testing::Test {
protected:
    void SetUp() override {
        int data[] = { 0, 1, 2, 3, 4, 5 };
        matrix = new Matrix<int>(2, 3, data);
    }

    void TearDown() override {
        delete matrix;
    }

    Matrix<int>* matrix = nullptr;
};

TEST_F(Matrix_test, copy) {
    int data[] = { 0, 1, 2, 3, 4, 5 };
    Matrix<int>* a = new Matrix<int>(2, 3, data);
    Matrix<int> b = *a;
    delete a;
    EXPECT_EQ(2, b.rows());
    EXPECT_EQ(3, b.columns());
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_EQ(data[i * 3 + j], b(i, j));
}

TEST_F(Matrix_test, index_operator) {
    EXPECT_EQ(5, (*matrix)(1, 2));
    EXPECT_THROW((*matrix)(-1, -1), std::out_of_range);
    EXPECT_THROW((*matrix)(9, 9), std::out_of_range);
    (*matrix)(1, 2) = 555;
    EXPECT_EQ(555, (*matrix)(1, 2));
}

TEST_F(Matrix_test, positive) {
    EXPECT_TRUE(+(*matrix) == (*matrix));
}

TEST_F(Matrix_test, add) {
    int data[] = { 1, 1, 1, 1, 1, 1 };
    int sum[] = { 1, 2, 3, 4, 5, 6 };
    Matrix<int> m(2, 3, data), s(2, 3, sum);
    EXPECT_TRUE((*matrix) + m == s);
    Matrix<int> m2(2, 4);
    EXPECT_THROW((*matrix) + m2, std::invalid_argument);
}

TEST_F(Matrix_test, negative) {
    int data[] = { 0, -1, -2, -3, -4, -5 };
    Matrix<int> m(2, 3, data);
    EXPECT_TRUE(-(*matrix) == m);
}

TEST_F(Matrix_test, sub) {
    int data[] = { 1, 1, 1, 1, 1, 1 };
    int diff[] = { -1, 0, 1, 2, 3, 4 };
    Matrix<int> m(2, 3, data), d(2, 3, diff);
    EXPECT_TRUE((*matrix) - m == d);
    Matrix<int> m2(2, 4);
    EXPECT_THROW((*matrix) - m2, std::invalid_argument);
}

TEST_F(Matrix_test, mul) {
    int data[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int product[] = { 13, 10, 7, 4, 76, 64, 52, 40 };
    Matrix<int> m(3, 4, data), p(2, 4, product);
    EXPECT_TRUE((*matrix) * m == p);
    Matrix<int> m2(2, 4);
    EXPECT_THROW((*matrix) * m2, std::invalid_argument);
}

TEST_F(Matrix_test, transpose) {
    int data[] = { 0, 3, 1, 4, 2, 5 };
    Matrix<int> transpose(3, 2, data);
    EXPECT_TRUE(matrix->transpose() == transpose);
}
