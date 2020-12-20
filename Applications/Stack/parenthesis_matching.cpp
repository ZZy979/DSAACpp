#include "parenthesis_matching.h"
#include "Stack/Array_stack.h"

using std::endl;

void print_matched_parentheses(string expr, ostream& os)
{
	Array_stack<int> s;
	for (int i = 0; i < expr.length(); ++i)
		if (expr[i] == '(')
			s.push(i);
		else if (expr[i] == ')') {
			try {
				// ´ÓÕ»ÖÐÉ¾³ýÆ¥ÅäµÄ×óÀ¨ºÅ
				os << s.top() << " matches " << i << endl;
				s.pop();
			}
			catch (Stack_empty) {
				// Õ»Îª¿Õ£¬Ã»ÓÐÆ¥ÅäµÄ×óÀ¨ºÅ
				os << "No match for right parenthesis at " << i << endl;
			}
		}
	// Õ»²»Îª¿Õ£¬Ê£ÓàÔÚÕ»ÖÐµÄ×óÀ¨ºÅÊÇ²»Æ¥ÅäµÄ
	while (!s.empty()) {
		os << "No match for left parenthesis at " << s.top() << endl;
		s.pop();
	}
}
