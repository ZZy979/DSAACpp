#pragma once
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Stack.h"
#include "../utils.h"

using std::ostringstream;
using std::invalid_argument;
using std::copy;

// ջ������ʵ��
template<class T>
class Array_stack : public Stack<T>
{
	T* element;     // �洢Ԫ�ص�һά����
	int space;      // ���������
	int sz;         // Ԫ�ظ���
public:
	explicit Array_stack(int capacity = 10);
	Array_stack(const Array_stack<T>& s);

	~Array_stack() { delete[] element; }

	Array_stack<T>& operator=(const Array_stack<T>& s);

	bool empty() const override { return sz == 0; }

	int size() const override { return sz; }

	void push(const T& value) override;
	void pop() override;
	T& top() override;
	const T& top() const override;

};

// ���캯�������capacity<=0���׳�invalid_argument�쳣
template<class T>
Array_stack<T>::Array_stack(int capacity)
{
	if (capacity <= 0) {
		ostringstream oss;
		oss << "initial capacity = " << capacity << ", must be positive";
		throw invalid_argument(oss.str());
	}
	space = capacity;
	element = new T[space];
	sz = 0;
}

template<class T>
Array_stack<T>::Array_stack(const Array_stack<T>& s)
{
	space = s.space;
	sz = s.sz;
	element = new T[space];
	copy(s.element, s.element + s.sz, element);
}

template<class T>
Array_stack<T>& Array_stack<T>::operator=(const Array_stack<T>& s)
{
	if (this != &s) {
		delete[] element;
		element = new T[s.space];
		copy(s.element, s.element + s.sz, element);
		space = s.space;
		sz = s.sz;
	}
	return *this;
}

template<class T>
void Array_stack<T>::push(const T& value)
{
	if (sz == space) {
		change_length_1d(element, space, 2 * space);
		space *= 2;
	}
	element[sz++] = value;
}

template<class T>
void Array_stack<T>::pop()
{
	check_empty();
	element[--sz].~T();
}

template<class T>
T& Array_stack<T>::top()
{
	check_empty();
	return element[sz - 1];
}

template<class T>
const T& Array_stack<T>::top() const
{
	check_empty();
	return element[sz - 1];
}
