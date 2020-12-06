#pragma once

// ����ڵ�
template<class T>
struct List_node
{
	T value;
	List_node<T>* next;

	List_node() :value(), next(nullptr) {}

	explicit List_node(const T& v) :value(v), next(nullptr) {}

	List_node(const T& v, List_node<T>* p) :value(v), next(p) {}
};
