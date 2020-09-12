#pragma once
#include <algorithm>
#include <stdexcept>

using std::copy;
using std::min;
using std::invalid_argument;

// 改变一维数组a的长度
// 如果new_length<=0则抛出invalid_argument异常
template<class T>
void change_length_1d(T*& a, int old_length, int new_length)
{
	if (new_length <= 0)
		throw invalid_argument("new_length must be > 0");
	T* temp = new T[new_length];
	copy(a, a + min(old_length, new_length), temp);
	delete[] a;
	a = temp;
}
