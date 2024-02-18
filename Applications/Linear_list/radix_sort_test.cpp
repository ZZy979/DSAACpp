#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include "student.h"
#include "radix_sort.h"

using std::srand;
using std::rand;
using std::clock;
using std::clock_t;
using std::ostringstream;
using std::vector;

TEST(Radix_sort_test, correctness) {
    int a[] = { 216, 521, 425, 116, 91, 515, 124, 34, 96, 24 };
    Linked_list<int> list;
    for (int x : a)
        list.push_back(x);
    radix_sort(list, 10);
    int prev = list[0];
    auto p = list.begin();
    for (++p; p != list.end(); prev = *p, ++p)
        EXPECT_TRUE(prev < *p);
}

TEST(Radix_sort_test, correctness2) {
    vector<string> names{ "A", "B", "C", "D", "E", "F" };
    vector<int> scores{ 500, 80, 6, 50, 800, 800 };
    Linked_list<Student> students;
    for (int i = names.size() - 1; i >= 0; --i)
        students.insert(0, Student(names[i], scores[i]));
    radix_sort(students, 10);

    vector<string> sorted_names{ "C", "D", "B", "A", "E", "F" };
    vector<int> sorted_scores{ 6, 50, 80, 500, 800, 800 };
    int i = 0;
    for (auto p = students.begin(); p != students.end(); ++p, ++i) {
        EXPECT_EQ(sorted_names[i], p->name);
        EXPECT_EQ(sorted_scores[i], p->score);
    }
}

TEST(Radix_sort_test, performance) {
    srand(42);
    vector<int> sizes{ 100, 1000, 10000 };
    for (int size : sizes) {
        Linked_list<int> list;
        for (int i = 0; i < size; ++i)
            list.insert(0, rand() % 1000);
        clock_t start = clock();
        radix_sort(list, 10);
        clock_t end = clock();
        std::cout << "size = " << size << ", time = "
            << (double(end) - start) / (CLOCKS_PER_SEC / 1000.0) << " ms" << std::endl;
    }
}

TEST(Radix_sort_test, performance2) {
    srand(42);
    Linked_list<int> list;
    for (int i = 0; i < 1000; ++i)
        list.insert(0, rand() % 1000);
    vector<int> radixes{ 2, 5, 10 };
    for (int r : radixes) {
        Linked_list<int> l = list;
        clock_t start = clock();
        radix_sort(l, r);
        clock_t end = clock();
        std::cout << "radix = " << r << ", time = "
            << (double(end) - start) / (CLOCKS_PER_SEC / 1000.0) << " ms" << std::endl;
    }
}
