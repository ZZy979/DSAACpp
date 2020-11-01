#include "CppUnitTest.h"
#include "Matrix/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Matrix_tests)
{
	Matrix<int>* matrix = nullptr;
public:
	TEST_METHOD_INITIALIZE(setup)
	{
		int data[] = { 0, 1, 2, 3, 4, 5 };
		matrix = new Matrix<int>(2, 3, data);
	}

	TEST_METHOD_CLEANUP(teardown)
	{
		delete matrix;
	}

	TEST_METHOD(test_copy)
	{
		int data[] = { 0, 1, 2, 3, 4, 5 };
		Matrix<int>* a = new Matrix<int>(2, 3, data);
		Matrix<int> b = *a;
		delete a;
		Assert::AreEqual(2, b.rows());
		Assert::AreEqual(3, b.columns());
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 3; ++j)
				Assert::AreEqual(data[i * 3 + j], b(i, j));
	}

	TEST_METHOD(test_index_operator)
	{
		Assert::AreEqual(5, (*matrix)(1, 2));
		Assert::ExpectException<out_of_range>([this]() {(*matrix)(-1, -1); });
		Assert::ExpectException<out_of_range>([this]() {(*matrix)(9, 9); });
		(*matrix)(1, 2) = 555;
		Assert::AreEqual(555, (*matrix)(1, 2));
	}

	TEST_METHOD(test_positive)
	{
		Assert::IsTrue(+(*matrix) == (*matrix));
	}

	TEST_METHOD(test_add)
	{
		int data[] = { 1, 1, 1, 1, 1, 1 };
		int sum[] = { 1, 2, 3, 4, 5, 6 };
		Matrix<int> m(2, 3, data), s(2, 3, sum);
		Assert::IsTrue((*matrix) + m == s);
		Matrix<int> m2(2, 4);
		Assert::ExpectException<invalid_argument>([this, &m2]() { (*matrix) + m2; });
	}

	TEST_METHOD(test_negative)
	{
		int data[] = { 0, -1, -2, -3, -4, -5 };
		Matrix<int> m(2, 3, data);
		Assert::IsTrue(-(*matrix) == m);
	}

	TEST_METHOD(test_sub)
	{
		int data[] = { 1, 1, 1, 1, 1, 1 };
		int diff[] = { -1, 0, 1, 2, 3, 4 };
		Matrix<int> m(2, 3, data), d(2, 3, diff);
		Assert::IsTrue((*matrix) - m == d);
		Matrix<int> m2(2, 4);
		Assert::ExpectException<invalid_argument>([this, &m2]() { (*matrix) - m2; });
	}

	TEST_METHOD(test_mul)
	{
		int data[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		int product[] = { 13, 10, 7, 4, 76, 64, 52, 40 };
		Matrix<int> m(3, 4, data), p(2, 4, product);
		Assert::IsTrue((*matrix) * m == p);
		Matrix<int> m2(2, 4);
		Assert::ExpectException<invalid_argument>([this, &m2]() { (*matrix) * m2; });
	}

	TEST_METHOD(test_transpose)
	{
		int data[] = { 0, 3, 1, 4, 2, 5 };
		Matrix<int> transpose(3, 2, data);
		Assert::IsTrue(matrix->transpose() == transpose);
	}
};
}
