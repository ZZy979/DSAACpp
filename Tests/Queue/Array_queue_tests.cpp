#include "CppUnitTest.h"
#include "Queue/Array_queue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Array_queue_tests)
{
	Array_queue<int> queue;
public:
	TEST_METHOD_INITIALIZE(setup)
	{
		queue.push(1);
		queue.push(2);
		queue.push(3);
		queue.push(4);
		queue.push(5);
	}

	TEST_METHOD(test_constructor)
	{
		Queue<int>* a = new Array_queue<int>(20);
		delete a;
		Array_queue<int> b(queue);
		Assert::ExpectException<invalid_argument>([&b]() { b = Array_queue<int>(-1); });
	}

	TEST_METHOD(test_copy)
	{
		Array_queue<int>* a = new Array_queue<int>();
		for (int i = 0; i < 4; ++i)
			a->push(i);
		Array_queue<int> b;
		b = *a;
		delete a;
		Assert::AreEqual(4, b.size());
		for (int i = 0; i < 4; ++i) {
			Assert::AreEqual(i, b.front());
			b.pop();
		}
	}

	TEST_METHOD(test_size_and_empty)
	{
		Array_queue<int> a;
		Assert::AreEqual(0, a.size());
		Assert::IsTrue(a.empty());
		a.push(8);
		Assert::AreEqual(1, a.size());
		Assert::IsFalse(a.empty());
	}

	TEST_METHOD(test_push)
	{
		Array_queue<int> a(2);
		a.push(1);
		a.push(2);
		Assert::AreEqual(1, a.front());
		Assert::AreEqual(2, a.back());
	}

	TEST_METHOD(test_pop)
	{
		queue.pop();
		Assert::AreEqual(4, queue.size());
		Assert::AreEqual(2, queue.front());
		Assert::AreEqual(5, queue.back());
		queue.clear();
		Assert::ExpectException<Queue_empty>([this]() { queue.pop(); });
	}

	TEST_METHOD(test_front_and_back)
	{
		Assert::AreEqual(1, queue.front());
		Assert::AreEqual(5, queue.back());
		queue.clear();
		Assert::ExpectException<Queue_empty>([this]() { queue.front(); });
		Assert::ExpectException<Queue_empty>([this]() { queue.back(); });
	}

	TEST_METHOD(test_clear)
	{
		queue.clear();
		Assert::IsTrue(queue.empty());
	}

};
}
