#include <gtest/gtest.h>

#include "ADT/Stack/Array_stack.h"

class Array_stack_test : public ::testing::Test {
protected:
    void SetUp() override {
        stack.push(3);
        stack.push(2);
        stack.push(7);
        stack.push(6);
        stack.push(8);
    }

    Array_stack<int> stack;
};

TEST_F(Array_stack_test, constructor) {
    Stack<double>* a = new Array_stack<double>(20);
    delete a;
    Array_stack<int> b(stack);
    EXPECT_THROW(b = Array_stack<int>(-1), std::invalid_argument);
}

TEST_F(Array_stack_test, copy) {
    Array_stack<int> *a = new Array_stack<int>();
    for (int i = 0; i < 4; ++i)
        a->push(i);
    Array_stack<int> b;
    b = *a;
    delete a;
    EXPECT_EQ(4, b.size());
    for (int i = 3; i >= 0; --i) {
        EXPECT_EQ(i, b.top());
        b.pop();
    }
}

TEST_F(Array_stack_test, size_and_empty) {
    Array_stack<int> a;
    EXPECT_EQ(0, a.size());
    EXPECT_TRUE(a.empty());
    a.push(8);
    EXPECT_EQ(1, a.size());
    EXPECT_FALSE(a.empty());
}

TEST_F(Array_stack_test, push) {
    stack.push(1);
    EXPECT_EQ(6, stack.size());
    EXPECT_EQ(1, stack.top());
}

TEST_F(Array_stack_test, pop) {
    stack.pop();
    EXPECT_EQ(4, stack.size());
    EXPECT_EQ(6, stack.top());
    stack.clear();
    EXPECT_THROW(stack.pop(), Stack_empty);
}

TEST_F(Array_stack_test, top) {
    EXPECT_EQ(8, stack.top());
    stack.clear();
    EXPECT_THROW(stack.top(), Stack_empty);
}

TEST_F(Array_stack_test, clear) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}
