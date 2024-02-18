#include <gtest/gtest.h>

#include "ADT/Queue/Array_queue.h"

class Array_queue_test : public ::testing::Test {
protected:
    void SetUp() override {
        queue.push(1);
        queue.push(2);
        queue.push(3);
        queue.push(4);
        queue.push(5);
    }

    Array_queue<int> queue;
};

TEST_F(Array_queue_test, constructor) {
    Queue<int>* a = new Array_queue<int>(20);
    delete a;
    Array_queue<int> b(queue);
    EXPECT_THROW(b = Array_queue<int>(-1), std::invalid_argument);
}

TEST_F(Array_queue_test, copy) {
    Array_queue<int>* a = new Array_queue<int>();
    for (int i = 0; i < 4; ++i)
        a->push(i);
    Array_queue<int> b;
    b = *a;
    delete a;
    EXPECT_EQ(4, b.size());
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(i, b.front());
        b.pop();
    }
}

TEST_F(Array_queue_test, size_and_empty) {
    Array_queue<int> a;
    EXPECT_EQ(0, a.size());
    EXPECT_TRUE(a.empty());
    a.push(8);
    EXPECT_EQ(1, a.size());
    EXPECT_FALSE(a.empty());
}

TEST_F(Array_queue_test, push) {
    Array_queue<int> a(2);
    a.push(1);
    a.push(2);
    EXPECT_EQ(1, a.front());
    EXPECT_EQ(2, a.back());
}

TEST_F(Array_queue_test, pop) {
    queue.pop();
    EXPECT_EQ(4, queue.size());
    EXPECT_EQ(2, queue.front());
    EXPECT_EQ(5, queue.back());
    queue.clear();
    EXPECT_THROW(queue.pop(), Queue_empty);
}

TEST_F(Array_queue_test, front_and_back) {
    EXPECT_EQ(1, queue.front());
    EXPECT_EQ(5, queue.back());
    queue.clear();
    EXPECT_THROW(queue.front(), Queue_empty);
    EXPECT_THROW(queue.back(), Queue_empty);
}

TEST_F(Array_queue_test, clear) {
    queue.clear();
    EXPECT_TRUE(queue.empty());
}
