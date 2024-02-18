#include "ADT/Linear_list/Vector_list.h"

#include <string>

#include <gtest/gtest.h>

class Vector_list_test : public ::testing::Test {
protected:
    void SetUp() override {
        // [0, 1, 2, 3, 4, 5]
        list = Vector_list<int>(2);
        for (int i = 0; i < 6; ++i)
            list.push_back(i);
    }

    Vector_list<int> list;
};

TEST_F(Vector_list_test, constructor) {
    Linear_list<double>* a = new Vector_list<double>(20);
    delete a;
    Vector_list<int> b(list);
    EXPECT_TRUE(b == list);
    EXPECT_THROW(b = Vector_list<int>(-1), std::invalid_argument);
}

TEST_F(Vector_list_test, capacity) {
    Vector_list<int> a(8), b;
    EXPECT_EQ(8, a.capacity());
    EXPECT_EQ(10, b.capacity());
}

TEST_F(Vector_list_test, size_and_empty) {
    Vector_list<int> v;
    EXPECT_EQ(0, v.size());
    EXPECT_TRUE(v.empty());
    v.insert(0, 8);
    EXPECT_EQ(1, v.size());
    EXPECT_FALSE(v.empty());
}

TEST_F(Vector_list_test, get) {
    EXPECT_EQ(4, list.get(4));
    EXPECT_THROW(list.get(7), std::out_of_range);
}

TEST_F(Vector_list_test, set) {
    int v = list.set(3, 333);
    EXPECT_EQ(333, list[3]);
    EXPECT_EQ(3, v);
    EXPECT_THROW(list.set(7, 777), std::out_of_range);
}


TEST_F(Vector_list_test, index_of) {
    EXPECT_EQ(4, list.index_of(4));
    EXPECT_EQ(-1, list.index_of(7));
}

TEST_F(Vector_list_test, push_back) {
    Vector_list<int> v(1);
    EXPECT_EQ(0, v.size());
    v.push_back(8);
    EXPECT_EQ(1, v.size());
    EXPECT_EQ(8, v[0]);
    v.push_back(9);
    EXPECT_EQ(2, v.size());
    EXPECT_EQ(9, v[1]);
    EXPECT_EQ(2, v.capacity());
}

TEST_F(Vector_list_test, pop_back) {
    Vector_list<int> v;
    v.push_back(8);
    EXPECT_EQ(1, v.size());
    v.pop_back();
    EXPECT_EQ(0, v.size());
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST_F(Vector_list_test, insert) {
    EXPECT_EQ(6, list.size());
    for (int i = 0; i < list.size(); ++i)
        EXPECT_EQ(i, list[i]);
    list.push_back(6);
    EXPECT_EQ(7, list.size());
    EXPECT_EQ(6, list[6]);
    EXPECT_THROW(list.insert(9, 999), std::out_of_range);
}

TEST_F(Vector_list_test, erase) {
    list.erase(1);
    EXPECT_EQ(5, list.size());
    EXPECT_EQ(2, list[1]);
    list.pop_back();
    EXPECT_EQ(4, list.size());
    EXPECT_THROW(list.erase(-1), std::out_of_range);
}

TEST_F(Vector_list_test, clear) {
    list.clear();
    EXPECT_EQ(0, list.size());
}

TEST_F(Vector_list_test, output) {
    ostringstream oss;
    list.output(oss);
    EXPECT_EQ(std::string("[0, 1, 2, 3, 4, 5]"), oss.str());
}

TEST_F(Vector_list_test, iterator) {
    int v = 0;
    for (Vector_list<int>::const_iterator p = list.begin(); p != list.end(); ++p)
        EXPECT_EQ(v++, *p);
    auto p = list.end();
    while (p != list.begin())
        EXPECT_EQ(--v, *(--p));
}

TEST_F(Vector_list_test, subscript) {
    EXPECT_EQ(0, list[0]);
    list[0] = 8;
    EXPECT_EQ(8, list[0]);
}

TEST_F(Vector_list_test, compare) {
    Vector_list<int> a(list), b(list);
    EXPECT_TRUE(a == list);
    EXPECT_TRUE(b == list);
    a[0] = 8;
    b.erase(5);
    EXPECT_TRUE(list < a);
    EXPECT_TRUE(b < list);
}
