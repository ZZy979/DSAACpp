#include <sstream>
#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

#include "Currency.h"

TEST(Currency_test, constructor) {
    Currency f, g(plus, 3, 45), h(minus, 10);

    EXPECT_EQ(plus, f.get_sign());
    EXPECT_EQ(0, f.get_dollars());
    EXPECT_EQ(0, f.get_cents());

    EXPECT_EQ(plus, g.get_sign());
    EXPECT_EQ(3, g.get_dollars());
    EXPECT_EQ(45, g.get_cents());

    EXPECT_EQ(minus, h.get_sign());
    EXPECT_EQ(10, h.get_dollars());
    EXPECT_EQ(0, h.get_cents());

    EXPECT_THROW(Currency(minus, 2, 305), std::invalid_argument);
}

TEST(Currency_test, set_value) {
    Currency c;

    c.set_value(minus, 2, 25);
    EXPECT_EQ(minus, c.get_sign());
    EXPECT_EQ(2, c.get_dollars());
    EXPECT_EQ(25, c.get_cents());

    c.set_value(-6.45);
    EXPECT_EQ(minus, c.get_sign());
    EXPECT_EQ(6, c.get_dollars());
    EXPECT_EQ(45, c.get_cents());

    EXPECT_THROW(c.set_value(plus, 3, 152), std::invalid_argument);
}

TEST(Currency_test, add) {
    Currency g(minus, 2, 25), h(plus, 3, 50), i(minus, 6, 45), j;

    j = h + g;
    EXPECT_DOUBLE_EQ(1.25, j.get_amount());

    j = i + g + h;
    EXPECT_DOUBLE_EQ(-5.20, j.get_amount());

    j = (i += g) + h;
    EXPECT_DOUBLE_EQ(-5.20, j.get_amount());
    EXPECT_DOUBLE_EQ(-8.70, i.get_amount());
}

TEST(Currency_test, arithmetic) {
    Currency a(527.88), b(235.96), c(-357.37);
    EXPECT_DOUBLE_EQ(-121.41, (b + c).get_amount());
    EXPECT_DOUBLE_EQ(291.92, (a - b).get_amount());
    EXPECT_DOUBLE_EQ(1728.28, (a * 3.274).get_amount());
    EXPECT_DOUBLE_EQ(-39.88, (c / 8.96).get_amount());
    EXPECT_DOUBLE_EQ(117.20, (b % 49.67).get_amount());
}

TEST(Currency_test, input) {
    Currency c;
    std::istringstream iss("-653.47");
    EXPECT_TRUE(iss >> c);
    EXPECT_EQ(minus, c.get_sign());
    EXPECT_EQ(653, c.get_dollars());
    EXPECT_EQ(47, c.get_cents());

    iss.clear();
    iss.str("abc@#$");
    EXPECT_FALSE(iss >> c);
}

TEST(Currency_test, output) {
    struct Test_case {
        Currency c;
        std::string expected;
    } test_cases[] = {
        {Currency(plus, 62, 3), "$62.03"},
        {Currency(minus, 4, 75), "-$4.75"}
    };
    for (const auto& t : test_cases) {
        std::ostringstream oss;
        oss << t.c;
        EXPECT_EQ(t.expected, oss.str());
    }
}
