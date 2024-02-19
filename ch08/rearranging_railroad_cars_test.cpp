#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "rearranging_railroad_cars.h"

using std::ostringstream;
using std::string;

TEST(Rearranging_railroad_cars_test, can_rearrange) {
    string expected = "car 2: input -> holding track 0\n"
        "car 5: input -> holding track 1\n"
        "car 8: input -> holding track 2\n"
        "car 1: input -> holding track 0\n"
        "car 3: input -> holding track 1\n"
        "car 6: input -> holding track 2\n"
        "car 0: input -> output\n"
        "car 1: holding track 0 -> output\n"
        "car 2: holding track 0 -> output\n"
        "car 3: holding track 1 -> output\n"
        "car 7: input -> holding track 0\n"
        "car 4: input -> output\n"
        "car 5: holding track 1 -> output\n"
        "car 6: holding track 2 -> output\n"
        "car 7: holding track 0 -> output\n"
        "car 8: holding track 2 -> output\n";
    ostringstream oss;
    EXPECT_TRUE(railroad({ 2, 5, 8, 1, 3, 6, 0, 7, 4 }, 3, oss));
    EXPECT_EQ(expected, oss.str());
}

TEST(Rearranging_railroad_cars_test, cannot_rearrange) {
    ostringstream oss;
    EXPECT_FALSE(railroad({ 1, 2, 3, 4, 5, 6, 7, 8, 0 }, 3, oss));
}
