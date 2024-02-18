#include "ADT/Linear_list/Circular_linked_list.h"

#include <string>

#include <gtest/gtest.h>

class Circular_linked_list_test : public ::testing::Test {
protected:
    void SetUp() override {
        // [0, 1, 2, 3, 4, 5]
        list = Circular_linked_list<int>();
        for (int i = 0; i < 6; ++i)
            list.push_back(i);
    }

    Circular_linked_list<int> list;
};

TEST_F(Circular_linked_list_test, constructor) {
    Linear_list<double>* a = new Circular_linked_list<double>();
    delete a;
    Circular_linked_list<int> b(list);
    EXPECT_TRUE(b == list);
}

TEST_F(Circular_linked_list_test, copy) {
    Circular_linked_list<int>* a = new Circular_linked_list<int>();
    for (int i = 0; i < 4; ++i)
        a->push_back(i);
    Circular_linked_list<int> b;
    b = *a;
    delete a;
    EXPECT_EQ(4, b.size());
    Circular_linked_list<int>::iterator p = b.begin();
    for (int i = 0; i < 4; ++i, ++p)
        EXPECT_EQ(i, *p);
}

TEST_F(Circular_linked_list_test, size_and_empty) {
    Circular_linked_list<int> l;
    EXPECT_EQ(0, l.size());
    EXPECT_TRUE(l.empty());
    l.insert(0, 8);
    EXPECT_EQ(1, l.size());
    EXPECT_FALSE(l.empty());
}

TEST_F(Circular_linked_list_test, get) {
    EXPECT_EQ(4, list.get(4));
    EXPECT_THROW(list.get(7), std::out_of_range);
}

TEST_F(Circular_linked_list_test, set) {
    int l = list.set(3, 333);
    EXPECT_EQ(333, list[3]);
    EXPECT_EQ(3, l);
    EXPECT_THROW(list.set(7, 777), std::out_of_range);
}


TEST_F(Circular_linked_list_test, index_of) {
    EXPECT_EQ(4, list.index_of(4));
    EXPECT_EQ(-1, list.index_of(7));
}

TEST_F(Circular_linked_list_test, push_back) {
    Circular_linked_list<int> l;
    EXPECT_EQ(0, l.size());
    l.push_back(8);
    EXPECT_EQ(1, l.size());
    EXPECT_EQ(8, l[0]);
    l.push_back(9);
    EXPECT_EQ(2, l.size());
    EXPECT_EQ(9, l[1]);
}

TEST_F(Circular_linked_list_test, pop_back) {
    Circular_linked_list<int> l;
    l.push_back(8);
    EXPECT_EQ(1, l.size());
    l.pop_back();
    EXPECT_EQ(0, l.size());
    EXPECT_THROW(l.pop_back(), std::out_of_range);
}

TEST_F(Circular_linked_list_test, insert) {
    EXPECT_EQ(6, list.size());
    int v = 0;
    for (auto p = list.begin(); p != list.end(); ++p)
        EXPECT_EQ(v++, *p);
    list.push_back(6);
    EXPECT_EQ(7, list.size());
    EXPECT_EQ(6, list[6]);
    EXPECT_THROW(list.insert(9, 999), std::out_of_range);
}

TEST_F(Circular_linked_list_test, erase) {
    list.erase(1);
    EXPECT_EQ(5, list.size());
    EXPECT_EQ(2, list[1]);
    list.pop_back();
    EXPECT_EQ(4, list.size());
    EXPECT_THROW(list.erase(-1), std::out_of_range);
}

TEST_F(Circular_linked_list_test, clear) {
    list.clear();
    EXPECT_EQ(0, list.size());
}

TEST_F(Circular_linked_list_test, output) {
    ostringstream oss;
    list.output(oss);
    EXPECT_EQ(std::string("[0, 1, 2, 3, 4, 5]"), oss.str());
}

TEST_F(Circular_linked_list_test, iterator) {
    int v = 0;
    for (Circular_linked_list<int>::iterator p = list.begin(); p != list.end(); ++p)
        EXPECT_EQ(v++, *p);
}

TEST_F(Circular_linked_list_test, set_size) {
    list.set_size(10);
    EXPECT_EQ(6, list.size());
    list.set_size(3);
    EXPECT_EQ(3, list.size());
    list.set_size(-1);
    EXPECT_EQ(0, list.size());
}

TEST_F(Circular_linked_list_test, subscript) {
    EXPECT_EQ(0, list[0]);
    list[0] = 8;
    EXPECT_EQ(8, list[0]);
}

TEST_F(Circular_linked_list_test, last_index_of) {
    EXPECT_EQ(2, list.last_index_of(2));
    list[4] = 2;
    EXPECT_EQ(4, list.last_index_of(2));
    EXPECT_EQ(-1, list.last_index_of(7));
}

TEST_F(Circular_linked_list_test, compare) {
    Circular_linked_list<int> a(list), b(list);
    EXPECT_TRUE(a == list);
    EXPECT_TRUE(b == list);
    a.set(0, 8);
    b.erase(5);
    EXPECT_TRUE(list < a);
    EXPECT_TRUE(b < list);
}

TEST_F(Circular_linked_list_test, swap) {
    Circular_linked_list<int> a(list), b(list), c;
    c.swap(b);
    EXPECT_TRUE(a == c);
}

TEST_F(Circular_linked_list_test, remove_range) {
    list.remove_range(1, 4);
    EXPECT_EQ(3, list.size());
    Circular_linked_list<int> l;
    l.push_back(0);
    l.push_back(4);
    l.push_back(5);
    EXPECT_TRUE(l == list);
}
