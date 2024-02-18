#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

// 栈的应用：汉诺塔
// 将n个盘子从塔0移到塔2，用塔1作为中转，返回移动步骤
vector<string> hanoi(int n);
