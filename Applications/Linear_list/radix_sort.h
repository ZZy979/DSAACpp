#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include "Linear_list/Linked_list.h"
#include "bin_sort.h"

using std::vector;

int log(int a, int b)
{
	return int(std::log(b) / std::log(a));
}

// ���Ա��Ӧ�ã���������
// ʹ��f��ÿ��Ԫ��ת��Ϊ����������Ϊr
template<class T, class F>
void radix_sort(Linked_list<T>& list, F f, int r)
{
	if (r < 2)
		throw std::invalid_argument("��������Ϊ2");
	vector<int> logs;
	for (T& x : list)
		if (f(x) > 0)
			logs.push_back(log(r, f(x)));
	int d = *std::max_element(logs.begin(), logs.end());
	// Ԫ�ط�Χ[0, r^(d+1)-1]
	// ����r=10,d=2����ΧΪ[0, 999]
	for (int k = 0, p = 1; k <= d; ++k, p *= r)
		bin_sort(list, [r, p](T t) { return t / p % r; }, r - 1);
}

// ��������ʹ��int(t)��Ԫ��ת��Ϊ����������Ϊr
template<class T>
void radix_sort(Linked_list<T>& list, int r)
{
	radix_sort(list, [](T t) { return int(t); }, r);
}
