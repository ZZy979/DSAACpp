#pragma once
#include <vector>

using std::vector;

// 栈的应用：确定开关盒是否可布线
// 开关盒周围有环形排列的2n个管脚，两个管脚通过一根线连接成一个网组
// net为每个管脚所属的网组编号
bool check_box(vector<int> net);
