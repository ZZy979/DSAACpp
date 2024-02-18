#include <sstream>

#include <gtest/gtest.h>

#include "parenthesis_matching.h"

using std::ostringstream;

TEST(Parenthesis_matching_test, all_match) {
    string expected = "0 matches 1\n3 matches 4\n2 matches 5\n";
    ostringstream oss;
    print_matched_parentheses("()(())", oss);
    EXPECT_EQ(expected, oss.str());
}

TEST(Parenthesis_matching_test, no_match_right) {
    string expected = "0 matches 1\nNo match for right parenthesis at 2\n";
    ostringstream oss;
    print_matched_parentheses("())", oss);
    EXPECT_EQ(expected, oss.str());
}

TEST(Parenthesis_matching_test, no_match_left) {
    string expected = "1 matches 2\nNo match for left parenthesis at 0\n";
    ostringstream oss;
    print_matched_parentheses("(()", oss);
    EXPECT_EQ(expected, oss.str());
}

TEST(Parenthesis_matching_test, empty) {
    ostringstream oss;
    print_matched_parentheses("", oss);
    EXPECT_EQ(string(), oss.str());
}
