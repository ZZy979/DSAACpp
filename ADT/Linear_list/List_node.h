#pragma once

// Á´±í½Úµã
template<class T>
struct List_node
{
	T value;
	List_node<T>* next;

	List_node() :value(), next(nullptr) {}

	explicit List_node(const T& l) :value(l), next(nullptr) {}

	List_node(const T& l, List_node<T>* p) :value(l), next(p) {}
};
