#include <string>
#include "CppUnitTest.h"
#include "Linear_list/Array_list.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Array_list_tests)
{
	Array_list<int> list;
public:

	TEST_METHOD_INITIALIZE(setup_class)
	{
		// [0, 1, 2, 3, 4, 5], capacity = 8
		// 自定义类包含动态数组指针时一定要自定义赋值运算符！！！否则会被内存越界坑一下午_(:з」∠)_
		list = Array_list<int>(2);
		list.insert(0, 1);
		list.insert(1, 5);
		list.insert(0, 0);
		list.insert(2, 3);
		list.insert(3, 4);
		list.insert(2, 2);
	}

	TEST_METHOD(test_constructor)
	{
		Linear_list<double>* a = new Array_list<double>(20);
		delete a;
		Array_list<int> b(2);
		b = Array_list<int>();
		Assert::ExpectException<invalid_argument>([&b]() { b = Array_list<int>(-1); });
	}

	TEST_METHOD(test_capacity)
	{
		Array_list<int> a(8), b;
		Assert::AreEqual(8, a.capacity());
		Assert::AreEqual(10, b.capacity());
	}

	TEST_METHOD(test_size_and_empty)
	{
		Array_list<int> a;
		Assert::AreEqual(0, a.size());
		Assert::IsTrue(a.empty());
		a.insert(0, 8);
		Assert::AreEqual(1, a.size());
		Assert::IsFalse(a.empty());
	}

	TEST_METHOD(test_get)
	{
		Assert::AreEqual(4, list.get(4));
		Assert::ExpectException<out_of_range>([this]() { list.get(7); });
	}

	TEST_METHOD(test_set)
	{
		int v = list.set(3, 333);
		Assert::AreEqual(333, list.get(3));
		Assert::AreEqual(3, v);
		Assert::ExpectException<out_of_range>([this]() { list.set(7, 777); });
	}


	TEST_METHOD(test_index_of)
	{
		Assert::AreEqual(4, list.index_of(4));
		Assert::AreEqual(-1, list.index_of(7));
	}

	TEST_METHOD(test_insert)
	{
		Assert::AreEqual(6, list.size());
		for (int i = 0; i < list.size(); ++i)
			Assert::AreEqual(i, list.get(i));
		Assert::AreEqual(8, list.capacity());
		list.push_back(6);
		Assert::AreEqual(7, list.size());
		Assert::AreEqual(6, list.get(6));
		Assert::ExpectException<out_of_range>([this]() { list.insert(9, 999); });
	}

	TEST_METHOD(test_erase)
	{
		list.erase(1);
		Assert::AreEqual(5, list.size());
		Assert::AreEqual(2, list.get(1));
		list.pop_back();
		Assert::AreEqual(4, list.size());
		Assert::ExpectException<out_of_range>([this]() { list.erase(-1); });
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
		for (Array_list<int>::iterator p = list.begin(); p != list.end(); ++p, ++v)
			Assert::AreEqual(v, *p);
		auto p = list.end();
		while (p != list.begin())
			Assert::AreEqual(--v, *(--p));
	}

};
}
