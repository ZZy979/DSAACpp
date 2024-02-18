#include <stdexcept>

#include <gtest/gtest.h>

#include "towers_of_hanoi.h"

TEST(Towers_of_hanoi_test, 1) {
    vector<string> expected_moves{ "0->2" };
    EXPECT_TRUE(expected_moves == hanoi(1));
}

TEST(Towers_of_hanoi_test, 3) {
    vector<string> expected_moves{
        "0->2", "0->1", "2->1", "0->2",
        "1->0", "1->2", "0->2"
    };
    EXPECT_TRUE(expected_moves == hanoi(3));
}

TEST(Towers_of_hanoi_test, 5) {
    vector<string> expected_moves{
        "0->2", "0->1", "2->1", "0->2", "1->0", "1->2", "0->2", "0->1",
        "2->1", "2->0", "1->0", "2->1", "0->2", "0->1", "2->1", "0->2",
        "1->0", "1->2", "0->2", "1->0", "2->1", "2->0", "1->0", "1->2",
        "0->2", "0->1", "2->1", "0->2", "1->0", "1->2", "0->2"
    };
    EXPECT_TRUE(expected_moves == hanoi(5));
}

TEST(Towers_of_hanoi_test, too_small) {
    EXPECT_THROW(hanoi(0), std::invalid_argument);
}

TEST(Towers_of_hanoi_test, too_large) {
    EXPECT_THROW(hanoi(20), std::invalid_argument);
}
