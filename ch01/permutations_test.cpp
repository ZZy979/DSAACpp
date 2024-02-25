#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "permutations.h"

TEST(Permutations_test, test) {
    int a[] = {1, 2, 3, 4};

    struct Test_case {
        int m;
        std::string expected;
    } test_cases[] = {
        {0, "1 \n"},
        {2, "1 2 3 \n1 3 2 \n2 1 3 \n2 3 1 \n3 2 1 \n3 1 2 \n"},
        {3, "1 2 3 4 \n1 2 4 3 \n1 3 2 4 \n1 3 4 2 \n1 4 3 2 \n1 4 2 3 \n"
            "2 1 3 4 \n2 1 4 3 \n2 3 1 4 \n2 3 4 1 \n2 4 3 1 \n2 4 1 3 \n"
            "3 2 1 4 \n3 2 4 1 \n3 1 2 4 \n3 1 4 2 \n3 4 1 2 \n3 4 2 1 \n"
            "4 2 3 1 \n4 2 1 3 \n4 3 2 1 \n4 3 1 2 \n4 1 3 2 \n4 1 2 3 \n"}
    };
    for (const auto& t : test_cases) {
        std::ostringstream oss;
        permutations(a, 0, t.m, oss);
        EXPECT_EQ(t.expected, oss.str());
    }
}
