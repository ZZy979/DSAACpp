#pragma once
#include "Linear_list/Linked_list.h"

// ���Ա��Ӧ�ã���������
// ʹ��f��ÿ��Ԫ��ת��Ϊ��������ΧΪ[0, max]
template<class T, class F>
void bin_sort(Linked_list<T>& list, F f, int max)
{
	vector<Linked_list<T> > bins(max + 1, Linked_list<T>());

	// ��Ԫ�ش�������ȡ�������䵽������
	int n = list.size();
	for (int i = 0; i < n; ++i) {
		T elem = list[0];
		list.erase(0);
		bins[f(elem)].insert(0, elem);
	}

	// ���������ռ�Ԫ��
	for (int i = max; i >= 0; --i)
		while (!bins[i].empty()) {
			T elem = bins[i][0];
			bins[i].erase(0);
			list.insert(0, elem);
		}
}

// ��������ʹ��int(t)��Ԫ��ת��Ϊ��������ΧΪ[0, max]
template<class T>
void bin_sort(Linked_list<T>& list, int max)
{
	bin_sort(list, [](T t) { return int(t); }, max);
}
