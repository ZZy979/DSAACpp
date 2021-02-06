#pragma once
#include <iostream>
#include <vector>

using std::ostream;
using std::vector;

// 栈的应用：列车车厢重排
// 车厢初始顺序为input_order，缓冲轨道最多为num_tracks，输出移动序列
// 如果能够完成车厢的重排则返回true
bool railroad(vector<int> input_order, int num_tracks, ostream& os = std::cout);
