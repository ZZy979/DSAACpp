#include <stdexcept>
#include "CppUnitTest.h"
#include "towers_of_hanoi.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Applications
{
TEST_CLASS(Towers_of_hanoi_tests)
{
	TEST_METHOD(test_1)
	{
		vector<string> expected_moves{ "0->2" };
		Assert::IsTrue(expected_moves == hanoi(1));
	}

	TEST_METHOD(test_3)
	{
		vector<string> expected_moves{
			"0->2", "0->1", "2->1", "0->2",
			"1->0", "1->2", "0->2"
		};
		Assert::IsTrue(expected_moves == hanoi(3));
	}

	TEST_METHOD(test_5)
	{
		vector<string> expected_moves{
			"0->2", "0->1", "2->1", "0->2", "1->0", "1->2", "0->2", "0->1",
			"2->1", "2->0", "1->0", "2->1", "0->2", "0->1", "2->1", "0->2",
			"1->0", "1->2", "0->2", "1->0", "2->1", "2->0", "1->0", "1->2",
			"0->2", "0->1", "2->1", "0->2", "1->0", "1->2", "0->2"
		};
		Assert::IsTrue(expected_moves == hanoi(5));
	}

	TEST_METHOD(test_too_small)
	{
		Assert::ExpectException<std::invalid_argument>([]() {hanoi(0); });
	}

	TEST_METHOD(test_too_large)
	{
		Assert::ExpectException<std::invalid_argument>([]() {hanoi(20); });
	}

};
}
