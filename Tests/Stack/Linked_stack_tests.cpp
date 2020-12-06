#include "CppUnitTest.h"
#include "Stack/Linked_stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Linked_stack_tests)
{
	Linked_stack<int> stack;
public:
	TEST_METHOD_INITIALIZE(setup)
	{
		stack.push(3);
		stack.push(2);
		stack.push(7);
		stack.push(6);
		stack.push(8);
	}

	TEST_METHOD(test_constructor)
	{
		Stack<double>* a = new Linked_stack<double>();
		delete a;
		Linked_stack<int> b(stack);
	}

	TEST_METHOD(test_copy)
	{
		Linked_stack<int>* a = new Linked_stack<int>();
		for (int i = 0; i < 4; ++i)
			a->push(i);
		Linked_stack<int> b;
		b = *a;
		delete a;
		Assert::AreEqual(4, b.size());
		for (int i = 3; i >= 0; --i) {
			Assert::AreEqual(i, b.top());
			b.pop();
		}
	}

	TEST_METHOD(test_size_and_empty)
	{
		Linked_stack<int> a;
		Assert::AreEqual(0, a.size());
		Assert::IsTrue(a.empty());
		a.push(8);
		Assert::AreEqual(1, a.size());
		Assert::IsFalse(a.empty());
	}

	TEST_METHOD(test_push)
	{
		stack.push(1);
		Assert::AreEqual(6, stack.size());
		Assert::AreEqual(1, stack.top());
	}

	TEST_METHOD(test_pop)
	{
		stack.pop();
		Assert::AreEqual(4, stack.size());
		Assert::AreEqual(6, stack.top());
		while (!stack.empty())
			stack.pop();
		Assert::ExpectException<Stack_empty>([this]() { stack.pop(); });
	}

	TEST_METHOD(test_top)
	{
		Assert::AreEqual(8, stack.top());
		while (!stack.empty())
			stack.pop();
		Assert::ExpectException<Stack_empty>([this]() { stack.top(); });
	}

};
}
