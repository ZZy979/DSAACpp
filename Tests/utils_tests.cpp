#include "CppUnitTest.h"
#include "utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Utils_tests)
{
public:

	TEST_METHOD(test_change_length_1d)
	{
		int r = 5, r2 = 10, r3 = 4;
		int* a = new int[r] {0, 1, 2, 3, 4};

		change_length_1d(a, r, r2);
		for (int i = 0; i < r; ++i)
			Assert::AreEqual(i, a[i]);

		change_length_1d(a, r2, r3);
		for (int i = 0; i < r3; ++i)
			Assert::AreEqual(i, a[i]);

		Assert::ExpectException<invalid_argument>([&a, r3]() { change_length_1d(a, r3, 0); });
		delete[] a;
	}

};
}
