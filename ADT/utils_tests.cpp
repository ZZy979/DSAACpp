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

	TEST_METHOD(test_change_length_2d)
	{
		int** a;
		int r = 4, c = 3;
		make_2d_array(a, r, c);
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				a[i][j] = i * c + j;

		int r2 = 5, c2 = 4;
		change_length_2d(a, r, c, r2, c2);
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				Assert::AreEqual(i * c + j, a[i][j]);

		int r3 = 3, c3 = 2;
		change_length_2d(a, r2, c2, r3, c3);
		for (int i = 0; i < r3; ++i)
			for (int j = 0; j < c3; ++j)
				Assert::AreEqual(i * c + j, a[i][j]);

		Assert::ExpectException<invalid_argument>([&a, r3, c3]() { change_length_2d(a, r3, c3, 0, 0); });
		delete_2d_array(a, r3);
	}

	TEST_METHOD(test_change_length_2d_2)
	{
		int** a;
		int r = 4, c[] = { 1, 4, 2, 3 };
		make_2d_array(a, r, c);
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c[i]; ++j)
				a[i][j] = i * 4 + j;

		int r2 = 3, c2[] = { 4, 2, 3 };
		change_length_2d(a, r, c, r2, c2);
		for (int i = 0; i < r2; ++i)
			for (int j = 0; j < min(c[i], c2[i]); ++j)
				Assert::AreEqual(i * 4 + j, a[i][j]);

		int r3 = 2, c3[] = { 3, 0 };
		Assert::ExpectException<invalid_argument>([&a, r2, c2, r3, c3]() { change_length_2d(a, r2, c2, r3, c3); });
		delete_2d_array(a, r2);
	}

};
}
