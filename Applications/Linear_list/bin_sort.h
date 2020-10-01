#pragma once
#include "Linear_list/Linked_list.h"

// 线性表的应用：箱子排序
// 使用f将每个元素转换为整数，范围为[0, max]
template<class T, class F>
void bin_sort(Linked_list<T>& list, F f, int max)
{
	vector<Linked_list<T> > bins(max + 1, Linked_list<T>());

	// 把元素从链表中取出，分配到箱子里
	int n = list.size();
	for (int i = 0; i < n; ++i) {
		T elem = list[0];
		list.erase(0);
		bins[f(elem)].insert(0, elem);
	}

	// 从箱子中收集元素
	for (int i = max; i >= 0; --i)
		while (!bins[i].empty()) {
			T elem = bins[i][0];
			bins[i].erase(0);
			list.insert(0, elem);
		}
}

// 箱子排序，使用int(t)将元素转换为整数，范围为[0, max]
template<class T>
void bin_sort(Linked_list<T>& list, int max)
{
	bin_sort(list, [](T t) { return int(t); }, max);
}
