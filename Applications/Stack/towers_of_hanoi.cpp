#include <iostream>
#include <stdexcept>
#include "towers_of_hanoi.h"
#include "Stack/Array_stack.h"

using std::cout;
using std::endl;
using std::invalid_argument;

// 全局变量，表示三个塔
Array_stack<int> tower[3];

// 全局变量，存储移动步骤
vector<string> moves;

// 将塔a顶部的盘子移到塔b
void move(int a, int b)
{
	int d = tower[a].top();
	tower[a].pop();
	tower[b].push(d);
	moves.push_back(std::to_string(a) + "->" + std::to_string(b));
}

void hanoi(int n, int a, int b, int c)
{
	if (n == 1)
		move(a, c);
	else {
		hanoi(n - 1, a, c, b);
		move(a, c);
		hanoi(n - 1, b, a, c);
	}
}

vector<string> hanoi(int n)
{
	if (n < 1)
		throw invalid_argument("n must be >= 1");
	else if (n > 10)
		throw invalid_argument("n must be <= 10");
	for (int i = 0; i < 3; ++i)
		tower[i].clear();
	for (int d = n; d > 0; --d)
		tower[0].push(d);
	moves.clear();
	hanoi(n, 0, 1, 2);
	return moves;
}
