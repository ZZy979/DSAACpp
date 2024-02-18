#include <gtest/gtest.h>

#include "offline_equivalence_class.h"

TEST(Offline_equivalence_class_test, 2_class) {
    EXPECT_EQ(2, equivalence_class(9, {
        {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 6},
        {3, 7}, {3, 8}, {4, 5}, {6, 7}, {6, 8} }));
}

TEST(Offline_equivalence_class_test, 1_class) {
    EXPECT_EQ(1, equivalence_class(5, { {0, 1}, {0, 2}, {1, 3}, {2, 4} }));
}

TEST(Offline_equivalence_class_test, empty_class) {
    EXPECT_EQ(3, equivalence_class(3, {}));
}
