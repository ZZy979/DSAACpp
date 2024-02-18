#pragma once
#include <sstream>
#include "Stack.h"
#include "../Linear_list/List_node.h"

using std::ostringstream;
using std::invalid_argument;

// 栈的链表实现
template<class T>
class Linked_stack : public Stack<T>
{
	List_node<T>* tp;  // 栈顶指针
	int sz;  // 元素个数

	void delete_top();
	void copy(const Linked_stack<T>& s);
public:
	Linked_stack() :tp(nullptr), sz(0) {}

	Linked_stack(const Linked_stack<T>& s) { copy(s); }

	~Linked_stack() { clear(); }

	Linked_stack<T>& operator=(const Linked_stack<T>& s);

	bool empty() const override { return sz == 0; }

	int size() const override { return sz; }

	void push(const T& value) override;
	void pop() override;
	T& top() override;
	const T& top() const override;
	void clear() override;

};

template<class T>
void Linked_stack<T>::delete_top()
{
	List_node<T>* next = tp->next;
	delete tp;
	tp = next;
}

template<class T>
void Linked_stack<T>::copy(const Linked_stack<T>& s)
{
	sz = s.sz;
	if (sz == 0) {
		tp = nullptr;
		return;
	}
	List_node<T>* from = s.tp;
	tp = new List_node<T>(from->value);
	from = from->next;
	List_node<T>* to = tp;
	while (from) {
		to->next = new List_node<T>(from->value);
		from = from->next;
		to = to->next;
	}
}

template<class T>
Linked_stack<T>& Linked_stack<T>::operator=(const Linked_stack<T>& s)
{
	if (this != &s) {
		clear();
		copy(s);
	}
	return *this;
}

template<class T>
void Linked_stack<T>::push(const T& value)
{
	tp = new List_node<T>(value, tp);
	++sz;
}

template<class T>
void Linked_stack<T>::pop()
{
	check_empty();
	delete_top();
	--sz;
}

template<class T>
T& Linked_stack<T>::top()
{
	check_empty();
	return tp->value;
}

template<class T>
const T& Linked_stack<T>::top() const
{
	check_empty();
	return tp->value;
}

template<class T>
void Linked_stack<T>::clear()
{
	while (tp)
		delete_top();
	sz = 0;
}
