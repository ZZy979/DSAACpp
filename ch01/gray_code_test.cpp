#include <gtest/gtest.h>

#include "gray_code.h"

TEST(Gray_code_test, test) {
    struct Test_case {
        int n;
        std::vector<int> expected;
    } test_cases[] = {
        {1, {1}},
        {2, {1, 2, 1}},
        {3, {1, 2, 1, 3, 1, 2, 1}},
        {4, {1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1}}
    };
    for (const auto& t : test_cases)
        EXPECT_EQ(t.expected, gray_code(t.n));
}
