#include <string>
#include "CppUnitTest.h"
#include "Linear_list/Linked_list.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Linked_list_tests)
{
	Linked_list<int> list;
public:
	TEST_METHOD_INITIALIZE(setup)
	{
		// [0, 1, 2, 3, 4, 5]
		list = Linked_list<int>();
		for (int i = 0; i < 6; ++i)
			list.push_back(i);
	}

	TEST_METHOD(test_constructor)
	{
		Linear_list<double>* a = new Linked_list<double>();
		delete a;
		Linked_list<int> b(list);
		Assert::IsTrue(b == list);
	}

	TEST_METHOD(test_copy)
	{
		Linked_list<int>* a = new Linked_list<int>();
		for (int i = 0; i < 4; ++i)
			a->push_back(i);
		Linked_list<int> b;
		b = *a;
		delete a;
		Assert::AreEqual(4, b.size());
		Linked_list<int>::iterator p = b.begin();
		for (int i = 0; i < 4; ++i, ++p)
			Assert::AreEqual(i, *p);
	}

	TEST_METHOD(test_size_and_empty)
	{
		Linked_list<int> l;
		Assert::AreEqual(0, l.size());
		Assert::IsTrue(l.empty());
		l.insert(0, 8);
		Assert::AreEqual(1, l.size());
		Assert::IsFalse(l.empty());
	}

	TEST_METHOD(test_get)
	{
		Assert::AreEqual(4, list.get(4));
		Assert::ExpectException<out_of_range>([this]() { list.get(7); });
	}

	TEST_METHOD(test_set)
	{
		int l = list.set(3, 333);
		Assert::AreEqual(333, list[3]);
		Assert::AreEqual(3, l);
		Assert::ExpectException<out_of_range>([this]() { list.set(7, 777); });
	}


	TEST_METHOD(test_index_of)
	{
		Assert::AreEqual(4, list.index_of(4));
		Assert::AreEqual(-1, list.index_of(7));
	}

	TEST_METHOD(test_push_back)
	{
		Linked_list<int> l;
		Assert::AreEqual(0, l.size());
		l.push_back(8);
		Assert::AreEqual(1, l.size());
		Assert::AreEqual(8, l[0]);
		l.push_back(9);
		Assert::AreEqual(2, l.size());
		Assert::AreEqual(9, l[1]);
	}

	TEST_METHOD(test_pop_back)
	{
		Linked_list<int> l;
		l.push_back(8);
		Assert::AreEqual(1, l.size());
		l.pop_back();
		Assert::AreEqual(0, l.size());
		Assert::ExpectException<out_of_range>([&l]() { l.pop_back(); });
	}

	TEST_METHOD(test_insert)
	{
		Assert::AreEqual(6, list.size());
		int v = 0;
		for (auto p = list.begin(); p != list.end(); ++p)
			Assert::AreEqual(v++, *p);
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
		for (Linked_list<int>::iterator p = list.begin(); p != list.end(); ++p)
			Assert::AreEqual(v++, *p);
	}

	TEST_METHOD(test_set_size)
	{
		list.set_size(10);
		Assert::AreEqual(6, list.size());
		list.set_size(3);
		Assert::AreEqual(3, list.size());
		list.set_size(-1);
		Assert::AreEqual(0, list.size());
	}

	TEST_METHOD(test_subscript)
	{
		Assert::AreEqual(0, list[0]);
		list[0] = 8;
		Assert::AreEqual(8, list[0]);
	}

	TEST_METHOD(test_last_index_of)
	{
		Assert::AreEqual(2, list.last_index_of(2));
		list[4] = 2;
		Assert::AreEqual(4, list.last_index_of(2));
		Assert::AreEqual(-1, list.last_index_of(7));
	}

	TEST_METHOD(test_compare)
	{
		Linked_list<int> a(list), b(list);
		Assert::IsTrue(a == list);
		Assert::IsTrue(b == list);
		a.set(0, 8);
		b.erase(5);
		Assert::IsTrue(list < a);
		Assert::IsTrue(b < list);
	}

	TEST_METHOD(test_swap)
	{
		Linked_list<int> a(list), b(list), c;
		c.swap(b);
		Assert::IsTrue(a == c);
	}

	TEST_METHOD(test_remove_range)
	{
		list.remove_range(1, 4);
		Assert::AreEqual(3, list.size());
		Linked_list<int> l;
		l.push_back(0);
		l.push_back(4);
		l.push_back(5);
		Assert::IsTrue(l == list);
	}

};
}
