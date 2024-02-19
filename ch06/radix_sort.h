#pragma once
#include <cmath>
#include <vector>
#include <algorithm>
#include "ADT/Linked_list.h"
#include "bin_sort.h"

using std::vector;

int log(int a, int b)
{
	return int(std::log(b) / std::log(a));
}

// 线性表的应用：基数排序
// 使用f将每个元素转换为整数，基数为r
template<class T, class F>
void radix_sort(Linked_list<T>& list, F f, int r)
{
	if (r < 2)
		throw std::invalid_argument("基数至少为2");
	vector<int> logs;
	for (T& x : list)
		if (f(x) > 0)
			logs.push_back(log(r, f(x)));
	int d = *std::max_element(logs.begin(), logs.end());
	// 元素范围[0, r^(d+1)-1]
	// 例如r=10,d=2，范围为[0, 999]
	for (int k = 0, p = 1; k <= d; ++k, p *= r)
		bin_sort(list, [r, p](T t) { return t / p % r; }, r - 1);
}

// 基数排序，使用int(t)将元素转换为整数，基数为r
template<class T>
void radix_sort(Linked_list<T>& list, int r)
{
	radix_sort(list, [](T t) { return int(t); }, r);
}
