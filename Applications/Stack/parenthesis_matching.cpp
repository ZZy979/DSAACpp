#include "parenthesis_matching.h"
#include "ADT/Stack/Array_stack.h"

using std::endl;

void print_matched_parentheses(string expr, ostream& os)
{
	Array_stack<int> s;
	for (int i = 0; i < expr.length(); ++i)
		if (expr[i] == '(')
			s.push(i);
		else if (expr[i] == ')') {
			try {
				// 从栈中删除匹配的左括号
				os << s.top() << " matches " << i << endl;
				s.pop();
			}
			catch (Stack_empty) {
				// 栈为空，没有匹配的左括号
				os << "No match for right parenthesis at " << i << endl;
			}
		}
	// 栈不为空，剩余在栈中的左括号是不匹配的
	while (!s.empty()) {
		os << "No match for left parenthesis at " << s.top() << endl;
		s.pop();
	}
}
