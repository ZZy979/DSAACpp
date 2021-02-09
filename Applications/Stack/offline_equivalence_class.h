#pragma once
#include <vector>

using std::vector;

// 栈的应用：离线等价类
// 输入元素个数n、r个关系对，返回等价类个数
int equivalence_class(int n, vector<vector<int>> relations);
