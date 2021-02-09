#include "CppUnitTest.h"
#include "offline_equivalence_class.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Applications
{
TEST_CLASS(Offline_equivalence_class_tests)
{
public:
	TEST_METHOD(test_2_class)
	{
		Assert::AreEqual(2, equivalence_class(9, {
			{0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 6},
			{3, 7}, {3, 8}, {4, 5}, {6, 7}, {6, 8} }));
	}

	TEST_METHOD(test_1_class)
	{
		Assert::AreEqual(1, equivalence_class(5, { {0, 1}, {0, 2}, {1, 3}, {2, 4} }));
	}

	TEST_METHOD(test_empty_class)
	{
		Assert::AreEqual(3, equivalence_class(3, {}));
	}

};
}
