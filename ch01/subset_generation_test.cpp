#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "subset_generation.h"

TEST(Subset_generation_test, test) {
    struct Test_case {
        int n;
        std::string expected;
    } test_cases[] = {
        {1, "0 \n1 \n"},
        {2, "0 0 \n0 1 \n1 0 \n1 1 \n"},
        {3, "0 0 0 \n0 0 1 \n0 1 0 \n0 1 1 \n1 0 0 \n1 0 1 \n1 1 0 \n1 1 1 \n"},
        {4, "0 0 0 0 \n0 0 0 1 \n0 0 1 0 \n0 0 1 1 \n0 1 0 0 \n0 1 0 1 \n0 1 1 0 \n0 1 1 1 \n"
            "1 0 0 0 \n1 0 0 1 \n1 0 1 0 \n1 0 1 1 \n1 1 0 0 \n1 1 0 1 \n1 1 1 0 \n1 1 1 1 \n"}
    };
    for (const auto& t : test_cases) {
        int* a = new int[t.n];
        std::ostringstream oss;
        subset(a, 0, t.n, oss);
        EXPECT_EQ(t.expected, oss.str());
        delete[] a;
    }
}
