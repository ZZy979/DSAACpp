#include <sstream>
#include <string>
#include "CppUnitTest.h"
#include "rearranging_railroad_cars.h"

using std::ostringstream;
using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Applications
{
TEST_CLASS(Rearranging_railroad_cars_tests)
{
public:
	TEST_METHOD(test_can_rearrange)
	{
		string expected = "car 2: input -> holding track 0\n"
			"car 5: input -> holding track 1\n"
			"car 8: input -> holding track 2\n"
			"car 1: input -> holding track 0\n"
			"car 3: input -> holding track 1\n"
			"car 6: input -> holding track 2\n"
			"car 0: input -> output\n"
			"car 1: holding track 0 -> output\n"
			"car 2: holding track 0 -> output\n"
			"car 3: holding track 1 -> output\n"
			"car 7: input -> holding track 0\n"
			"car 4: input -> output\n"
			"car 5: holding track 1 -> output\n"
			"car 6: holding track 2 -> output\n"
			"car 7: holding track 0 -> output\n"
			"car 8: holding track 2 -> output\n";
		ostringstream oss;
		Assert::IsTrue(railroad({ 2, 5, 8, 1, 3, 6, 0, 7, 4 }, 3, oss));
		Assert::AreEqual(expected, oss.str());
	}

	TEST_METHOD(test_cannot_rearrange)
	{
		ostringstream oss;
		Assert::IsFalse(railroad({ 1, 2, 3, 4, 5, 6, 7, 8, 0 }, 3, oss));
	}

};
}
