#pragma once
#include <algorithm>
#include <stdexcept>

using std::copy;
using std::min;
using std::invalid_argument;

// �ı�һά����a�ĳ���
// ���new_length<=0���׳�invalid_argument�쳣
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
