#include "CppUnitTest.h"
#include "switch_box_routing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Applications
{
TEST_CLASS(Switch_box_routing_tests)
{
public:
	TEST_METHOD(test_can_route)
	{
		Assert::IsTrue(check_box({ 0, 1, 1, 0, 2, 2, 3, 3 }));
	}

	TEST_METHOD(test_cannot_route)
	{
		Assert::IsFalse(check_box({ 0, 1, 1, 2, 0, 3, 2, 3 }));
	}

};
}
