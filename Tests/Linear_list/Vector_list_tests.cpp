#include <string>
#include "CppUnitTest.h"
#include "Linear_list/Vector_list.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Vector_list_tests)
{
	Vector_list<int> list;
public:
	TEST_METHOD_INITIALIZE(setup)
	{
		// [0, 1, 2, 3, 4, 5]
		list = Vector_list<int>(2);
		for (int i = 0; i < 6; ++i)
			list.push_back(i);
	}

	TEST_METHOD(test_constructor)
	{
		Linear_list<double>* a = new Vector_list<double>(20);
		delete a;
		Vector_list<int> b(list);
		Assert::IsTrue(b == list);
		Assert::ExpectException<invalid_argument>([&b]() { b = Vector_list<int>(-1); });
	}

	TEST_METHOD(test_capacity)
	{
		Vector_list<int> a(8), b;
		Assert::AreEqual(8, a.capacity());
		Assert::AreEqual(10, b.capacity());
	}

	TEST_METHOD(test_size_and_empty)
	{
		Vector_list<int> v;
		Assert::AreEqual(0, v.size());
		Assert::IsTrue(v.empty());
		v.insert(0, 8);
		Assert::AreEqual(1, v.size());
		Assert::IsFalse(v.empty());
	}

	TEST_METHOD(test_get)
	{
		Assert::AreEqual(4, list.get(4));
		Assert::ExpectException<out_of_range>([this]() { list.get(7); });
	}

	TEST_METHOD(test_set)
	{
		int v = list.set(3, 333);
		Assert::AreEqual(333, list[3]);
		Assert::AreEqual(3, v);
		Assert::ExpectException<out_of_range>([this]() { list.set(7, 777); });
	}


	TEST_METHOD(test_index_of)
	{
		Assert::AreEqual(4, list.index_of(4));
		Assert::AreEqual(-1, list.index_of(7));
	}

	TEST_METHOD(test_push_back)
	{
		Vector_list<int> v(1);
		Assert::AreEqual(0, v.size());
		v.push_back(8);
		Assert::AreEqual(1, v.size());
		Assert::AreEqual(8, v[0]);
		v.push_back(9);
		Assert::AreEqual(2, v.size());
		Assert::AreEqual(9, v[1]);
		Assert::AreEqual(2, v.capacity());
	}

	TEST_METHOD(test_pop_back)
	{
		Vector_list<int> v;
		v.push_back(8);
		Assert::AreEqual(1, v.size());
		v.pop_back();
		Assert::AreEqual(0, v.size());
		Assert::ExpectException<out_of_range>([&v]() { v.pop_back(); });
	}

	TEST_METHOD(test_insert)
	{
		Assert::AreEqual(6, list.size());
		for (int i = 0; i < list.size(); ++i)
			Assert::AreEqual(i, list[i]);
		list.push_back(6);
		Assert::AreEqual(7, list.size());
		Assert::AreEqual(6, list[6]);
		Assert::ExpectException<out_of_range>([this]() { list.insert(9, 999); });
	}

	TEST_METHOD(test_erase)
	{
		list.erase(1);
		Assert::AreEqual(5, list.size());
		Assert::AreEqual(2, list[1]);
		list.pop_back();
		Assert::AreEqual(4, list.size());
		Assert::ExpectException<out_of_range>([this]() { list.erase(-1); });
	}

	TEST_METHOD(test_clear)
	{
		list.clear();
		Assert::AreEqual(0, list.size());
	}

	TEST_METHOD(test_output)
	{
		ostringstream oss;
		list.output(oss);
		Assert::AreEqual(string("[0, 1, 2, 3, 4, 5]"), oss.str());
	}

	TEST_METHOD(test_iterator)
	{
		int v = 0;
		for (Vector_list<int>::const_iterator p = list.begin(); p != list.end(); ++p)
			Assert::AreEqual(v++, *p);
		auto p = list.end();
		while (p != list.begin())
			Assert::AreEqual(--v, *(--p));
	}

	TEST_METHOD(test_subscript)
	{
		Assert::AreEqual(0, list[0]);
		list[0] = 8;
		Assert::AreEqual(8, list[0]);
	}

	TEST_METHOD(test_compare)
	{
		Vector_list<int> a(list), b(list);
		Assert::IsTrue(a == list);
		Assert::IsTrue(b == list);
		a[0] = 8;
		b.erase(5);
		Assert::IsTrue(list < a);
		Assert::IsTrue(b < list);
	}

};
}
