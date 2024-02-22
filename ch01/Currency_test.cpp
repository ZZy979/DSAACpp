#include <sstream>
#include <stdexcept>

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
    EXPECT_EQ(plus, j.get_sign());
    EXPECT_EQ(1, j.get_dollars());
    EXPECT_EQ(25, j.get_cents());

    j = i + g + h;
    EXPECT_EQ(minus, j.get_sign());
    EXPECT_EQ(5, j.get_dollars());
    EXPECT_EQ(20, j.get_cents());

    j = (i += g) + h;
    EXPECT_EQ(minus, j.get_sign());
    EXPECT_EQ(5, j.get_dollars());
    EXPECT_EQ(20, j.get_cents());

    EXPECT_EQ(minus, i.get_sign());
    EXPECT_EQ(8, i.get_dollars());
    EXPECT_EQ(70, i.get_cents());
}

TEST(Currency_test, output) {
    Currency a(plus, 62, 3), b(minus, 4, 75);

    std::ostringstream oss;
    oss << a;
    EXPECT_EQ("$62.03", oss.str());

    oss.str("");
    oss << b;
    EXPECT_EQ("-$4.75", oss.str());
}
