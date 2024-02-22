#include <gtest/gtest.h>

#include "utils.h"

TEST(Utils_test, change_length_1d) {
    int r = 5, r2 = 10, r3 = 4;
    int* a = new int[r] {0, 1, 2, 3, 4};

    change_length_1d(a, r, r2);
    for (int i = 0; i < r; ++i)
        EXPECT_EQ(i, a[i]);

    change_length_1d(a, r2, r3);
    for (int i = 0; i < r3; ++i)
        EXPECT_EQ(i, a[i]);

    EXPECT_THROW(change_length_1d(a, r3, 0), std::invalid_argument);
    delete[] a;
}

TEST(Utils_test, change_length_2d) {
    int** a;
    int r = 4, c = 3;
    make_2d_array(a, r, c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            a[i][j] = i * c + j;

    int r2 = 5, c2 = 4;
    change_length_2d(a, r, c, r2, c2);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            EXPECT_EQ(i * c + j, a[i][j]);

    int r3 = 3, c3 = 2;
    change_length_2d(a, r2, c2, r3, c3);
    for (int i = 0; i < r3; ++i)
        for (int j = 0; j < c3; ++j)
            EXPECT_EQ(i * c + j, a[i][j]);

    EXPECT_THROW(change_length_2d(a, r3, c3, 0, 0), std::invalid_argument);
    delete_2d_array(a, r3);
}

TEST(Utils_test, change_length_2d_2) {
    int** a;
    int r = 4, c[] = { 1, 4, 2, 3 };
    make_2d_array(a, r, c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c[i]; ++j)
            a[i][j] = i * 4 + j;

    int r2 = 3, c2[] = { 4, 2, 3 };
    change_length_2d(a, r, c, r2, c2);
    for (int i = 0; i < r2; ++i)
        for (int j = 0; j < std::min(c[i], c2[i]); ++j)
            EXPECT_EQ(i * 4 + j, a[i][j]);

    int r3 = 2, c3[] = { 3, 0 };
    EXPECT_THROW(change_length_2d(a, r2, c2, r3, c3), std::invalid_argument);
    delete_2d_array(a, r2);
}
