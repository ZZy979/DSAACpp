#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include "bin_sort.h"
#include "student.h"

using std::srand;
using std::rand;
using std::clock;
using std::clock_t;
using std::ostringstream;
using std::vector;

TEST(Student_test, compare) {
    Student a("A", 90), b("A", 80), c("B", 90);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a != b);
}

TEST(Student_test, convert) {
    Student a("A", 90);
    EXPECT_EQ(90, int(a));
    EXPECT_TRUE(a > 80);
}

TEST(Student_test, output) {
    Student a("A", 90);
    ostringstream oss;
    oss << a;
    EXPECT_EQ(string("(A,90)\n"), oss.str());
}

TEST(Bin_sort_test, correctness) {
    vector<string> names{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
    vector<int> scores{ 2, 4, 5, 4, 3, 0, 4, 3, 4, 3 };
    Linked_list<Student> students;
    for (int i = names.size() - 1; i >= 0; --i)
        students.insert(0, Student(names[i], scores[i]));
    bin_sort(students, 5);
    
    vector<string> sorted_names{ "F", "A", "E", "H", "J", "B", "D", "G", "I", "C" };
    vector<int> sorted_scores{ 0, 2, 3, 3, 3, 4, 4, 4, 4, 5 };
    int i = 0;
    for (auto p = students.begin(); p != students.end(); ++p, ++i) {
        EXPECT_EQ(sorted_names[i], p->name);
        EXPECT_EQ(sorted_scores[i], p->score);
    }
}

TEST(Bin_sort_test, performance) {
    srand(42);
    vector<int> sizes{ 100, 1000, 10000 };
    int max_score = 100;
    for (int size : sizes) {
        Linked_list<Student> students;
        for (int i = 0; i < size; ++i)
            students.insert(0, Student("s" + std::to_string(i), rand() % (max_score + 1)));
        clock_t start = clock();
        bin_sort(students, max_score);
        clock_t end = clock();
        std::cout << "size = " << size << ", time = "
            << (double(end) - start) / (CLOCKS_PER_SEC / 1000.0) << " ms" << std::endl;
    }
}
