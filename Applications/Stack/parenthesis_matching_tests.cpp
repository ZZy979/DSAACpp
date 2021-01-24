#include <sstream>
#include "CppUnitTest.h"
#include "parenthesis_matching.h"

using std::ostringstream;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Applications
{
TEST_CLASS(Parenthesis_matching_tests)
{
public:
	TEST_METHOD(test_all_match)
	{
		string expected = "0 matches 1\n3 matches 4\n2 matches 5\n";
		ostringstream oss;
		print_matched_parentheses("()(())", oss);
		Assert::AreEqual(expected, oss.str());
	}

	TEST_METHOD(test_no_match_right)
	{
		string expected = "0 matches 1\nNo match for right parenthesis at 2\n";
		ostringstream oss;
		print_matched_parentheses("())", oss);
		Assert::AreEqual(expected, oss.str());
	}

	TEST_METHOD(test_no_match_left)
	{
		string expected = "1 matches 2\nNo match for left parenthesis at 0\n";
		ostringstream oss;
		print_matched_parentheses("(()", oss);
		Assert::AreEqual(expected, oss.str());
	}

	TEST_METHOD(test_empty)
	{
		ostringstream oss;
		print_matched_parentheses("", oss);
		Assert::AreEqual(string(), oss.str());
	}

};
}
