#include "CppUnitTest.h"
#include "Stack/Array_stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
TEST_CLASS(Array_stack_tests)
{
	Array_stack<int> stack;
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
		Stack<double>* a = new Array_stack<double>(20);
		delete a;
		Array_stack<int> b(stack);
		Assert::ExpectException<invalid_argument>([&b]() { b = Array_stack<int>(-1); });
	}

	TEST_METHOD(test_copy)
	{
		Array_stack<int> a;
		a = stack;
		Assert::AreEqual(stack.size(), a.size());
		while (!stack.empty()) {
			Assert::AreEqual(stack.top(), a.top());
			stack.pop();
			a.pop();
		}
	}

	TEST_METHOD(test_size_and_empty)
	{
		Array_stack<int> a;
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
