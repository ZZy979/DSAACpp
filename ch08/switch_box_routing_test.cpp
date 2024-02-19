#include <gtest/gtest.h>

#include "switch_box_routing.h"

TEST(Switch_box_routing_test, can_route) {
    EXPECT_TRUE(check_box({ 0, 1, 1, 0, 2, 2, 3, 3 }));
}

TEST(Switch_box_routing_test, cannot_route) {
    EXPECT_FALSE(check_box({ 0, 1, 1, 2, 0, 3, 2, 3 }));
}
