#include "switch_box_routing.h"
#include "Stack/Array_stack.h"

bool check_box(vector<int> net)
{
	Array_stack<int> s(net.size());
	for (int i = 0; i < net.size(); ++i)
		if (!s.empty())
			if (net[i] == net[s.top()])
				// 管脚i可布线
				s.pop();
			else
				s.push(i);
		else
			s.push(i);
	return s.empty();
}
