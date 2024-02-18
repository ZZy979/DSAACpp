#include <string>

#include <gtest/gtest.h>

#include "ADT/Linear_list/Array_list.h"

class Array_list_test : public ::testing::Test {
protected:
    void SetUp() override {
        // [0, 1, 2, 3, 4, 5], capacity = 8
        list = Array_list<int>(2);
        list.insert(0, 1);
        list.insert(1, 5);
        list.insert(0, 0);
        list.insert(2, 3);
        list.insert(3, 4);
        list.insert(2, 2);
    }

    Array_list<int> list;
};

TEST_F(Array_list_test, constructor) {
    Linear_list<double>* a = new Array_list<double>(20);
    delete a;
    Array_list<int> b(list);
    EXPECT_TRUE(b == list);
    EXPECT_THROW(b = Array_list<int>(-1), std::invalid_argument);
}

TEST_F(Array_list_test, copy) {
    Array_list<int>* a = new Array_list<int>(4);
    for (int i = 0; i < 4; ++i)
        a->push_back(i);
    Array_list<int> b;
    b = *a;
    delete a;
    EXPECT_EQ(4, b.size());
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(i, b[i]);
}

TEST_F(Array_list_test, capacity) {
    Array_list<int> a(8), b;
    EXPECT_EQ(8, a.capacity());
    EXPECT_EQ(10, b.capacity());
}

TEST_F(Array_list_test, size_and_empty) {
    Array_list<int> a;
    EXPECT_EQ(0, a.size());
    EXPECT_TRUE(a.empty());
    a.insert(0, 8);
    EXPECT_EQ(1, a.size());
    EXPECT_FALSE(a.empty());
}

TEST_F(Array_list_test, get) {
    EXPECT_EQ(4, list.get(4));
    EXPECT_THROW(list.get(7), std::out_of_range);
}

TEST_F(Array_list_test, set) {
    int v = list.set(3, 333);
    EXPECT_EQ(333, list[3]);
    EXPECT_EQ(3, v);
    EXPECT_THROW(list.set(7, 777), std::out_of_range);
}


TEST_F(Array_list_test, index_of) {
    EXPECT_EQ(4, list.index_of(4));
    EXPECT_EQ(-1, list.index_of(7));
}

TEST_F(Array_list_test, push_back) {
    Array_list<int> a(1);
    EXPECT_EQ(0, a.size());
    a.push_back(8);
    EXPECT_EQ(1, a.size());
    EXPECT_EQ(8, a[0]);
    a.push_back(9);
    EXPECT_EQ(2, a.size());
    EXPECT_EQ(9, a[1]);
    EXPECT_EQ(2, a.capacity());
}

TEST_F(Array_list_test, pop_back) {
    Array_list<int> a;
    a.push_back(8);
    EXPECT_EQ(1, a.size());
    a.pop_back();
    EXPECT_EQ(0, a.size());
    EXPECT_THROW(a.pop_back(), std::out_of_range);
}

TEST_F(Array_list_test, insert) {
    EXPECT_EQ(6, list.size());
    for (int i = 0; i < list.size(); ++i)
        EXPECT_EQ(i, list[i]);
    EXPECT_EQ(8, list.capacity());
    list.push_back(6);
    EXPECT_EQ(7, list.size());
    EXPECT_EQ(6, list[6]);
    EXPECT_THROW(list.insert(9, 999), std::out_of_range);
}

TEST_F(Array_list_test, erase) {
    list.erase(1);
    EXPECT_EQ(5, list.size());
    EXPECT_EQ(2, list[1]);
    list.pop_back();
    EXPECT_EQ(4, list.size());
    EXPECT_THROW(list.erase(-1), std::out_of_range);
}

TEST_F(Array_list_test, clear) {
    list.clear();
    EXPECT_EQ(0, list.size());
    EXPECT_EQ(8, list.capacity());
}

TEST_F(Array_list_test, output) {
    ostringstream oss;
    list.output(oss);
    EXPECT_EQ(std::string("[0, 1, 2, 3, 4, 5]"), oss.str());
}

TEST_F(Array_list_test, iterator) {
    int v = 0;
    for (Array_list<int>::iterator p = list.begin(); p != list.end(); ++p)
        EXPECT_EQ(v++, *p);
    auto p = list.end();
    while (p != list.begin())
        EXPECT_EQ(--v, *(--p));
}

TEST_F(Array_list_test, trim_to_size) {
    list.trim_to_size();
    EXPECT_EQ(list.size(), list.capacity());
    Array_list<int> a;
    a.trim_to_size();
    EXPECT_EQ(1, a.capacity());
}

TEST_F(Array_list_test, set_size) {
    list.set_size(10);
    EXPECT_EQ(6, list.size());
    list.set_size(3);
    EXPECT_EQ(3, list.size());
    list.set_size(-1);
    EXPECT_EQ(0, list.size());
}

TEST_F(Array_list_test, subscript) {
    EXPECT_EQ(0, list[0]);
    list[0] = 8;
    EXPECT_EQ(8, list[0]);
}

TEST_F(Array_list_test, last_index_of) {
    EXPECT_EQ(2, list.last_index_of(2));
    list[4] = 2;
    EXPECT_EQ(4, list.last_index_of(2));
    EXPECT_EQ(-1, list.last_index_of(7));
}

TEST_F(Array_list_test, compare) {
    Array_list<int> a(list), b(list);
    EXPECT_TRUE(a == list);
    EXPECT_TRUE(b == list);
    a[0] = 8;
    b.erase(5);
    EXPECT_TRUE(list < a);
    EXPECT_TRUE(b < list);
}

TEST_F(Array_list_test, swap) {
    Array_list<int> a(list), b(list), c;
    c.swap(b);
    EXPECT_TRUE(a == c);
}

TEST_F(Array_list_test, reserve) {
    list.reserve(4);
    EXPECT_EQ(8, list.capacity());
    list.reserve(10);
    EXPECT_EQ(10, list.capacity());
}

TEST_F(Array_list_test, remove_range) {
    list.remove_range(1, 4);
    EXPECT_EQ(3, list.size());
    Array_list<int> a(3);
    a.push_back(0);
    a.push_back(4);
    a.push_back(5);
    EXPECT_TRUE(a == list);
}
