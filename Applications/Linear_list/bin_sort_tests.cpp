#include "CppUnitTest.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include "student.h"
#include "bin_sort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::srand;
using std::rand;
using std::clock;
using std::clock_t;
using std::ostringstream;
using std::vector;

namespace Applications
{
TEST_CLASS(Student_tests)
{
public:
	TEST_METHOD(test_compare)
	{
		Student a("A", 90), b("A", 80), c("B", 90);
		Assert::IsTrue(a == c);
		Assert::IsTrue(a != b);
	}

	TEST_METHOD(test_convert)
	{
		Student a("A", 90);
		Assert::AreEqual(90, int(a));
		Assert::IsTrue(a > 80);
	}

	TEST_METHOD(test_output)
	{
		Student a("A", 90);
		ostringstream oss;
		oss << a;
		Assert::AreEqual(string("(A,90)\n"), oss.str());
	}

};

TEST_CLASS(Bin_sort_tests)
{
public:

	TEST_METHOD(test_correctness)
	{
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
			Assert::AreEqual(sorted_names[i], p->name);
			Assert::AreEqual(sorted_scores[i], p->score);
		}
	}

	TEST_METHOD(test_performance)
	{
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
			ostringstream oss;
			oss << "size = " << size << ", time = "
				<< (double(end) - start) / (CLOCKS_PER_SEC / 1000.0) << " ms" << std::endl;
			Logger::WriteMessage(oss.str().c_str());
		}
	}

};

}
