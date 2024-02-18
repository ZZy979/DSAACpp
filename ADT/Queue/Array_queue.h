#pragma once
#include <sstream>
#include <algorithm>
#include "Queue.h"

using std::ostringstream;
using std::invalid_argument;
using std::copy;

// 队列的数组实现
template<class T>
class Array_queue : public Queue<T>
{
	T* element;     // 存储元素的一维数组
	int space;      // 数组的容量
	int head;       // 队首指针
	int tail;       // 队尾指针
public:
	explicit Array_queue(int capacity = 16);
	Array_queue(const Array_queue<T>& q);

	~Array_queue() { delete[] element; }

	Array_queue<T>& operator=(const Array_queue<T>& q);

	bool empty() const override { return head == tail; }

	int size() const override { return tail - head; }

	void push(const T& value) override;
	void pop() override;
	T& front() override;
	const T& front() const override;
	T& back() override;
	const T& back() const override;

	void clear() override { tail = head; }

};

// 构造函数，如果capacity<=0则抛出invalid_argument异常
template<class T>
Array_queue<T>::Array_queue(int capacity)
{
	if (capacity <= 0) {
		ostringstream oss;
		oss << "initial capacity = " << capacity << ", must be positive";
		throw invalid_argument(oss.str());
	}
	space = capacity;
	element = new T[space];
	head = tail = 0;
}

template<class T>
Array_queue<T>::Array_queue(const Array_queue<T>& q)
{
	space = q.space;
	element = new T[space];
	copy(q.element, q.element + q.space, element);
	head = q.head;
	tail = q.tail;
}

template<class T>
Array_queue<T>& Array_queue<T>::operator=(const Array_queue<T>& q)
{
	if (this != &q) {
		delete[] element;
		space = q.space;
		element = new T[space];
		copy(q.element, q.element + q.space, element);
		head = q.head;
		tail = q.tail;
	}
	return *this;
}

template<class T>
void Array_queue<T>::push(const T& value)
{
	if ((tail + 1) % space == head) {
		T* new_element = new T[2 * space];
		if (head <= 1)
			// 没有形成环
			copy(element + head, element + head + space - 1, new_element);
		else {
			copy(element + head, element + space, new_element);
			copy(element, element + tail, new_element + space - head);
		}
		head = 0;
		tail = space - 1;
		space *= 2;
		delete[] element;
		element = new_element;
	}
	element[tail] = value;
	tail = (tail + 1) % space;
}

template<class T>
void Array_queue<T>::pop()
{
	this->check_empty();
	element[head].~T();
	head = (head + 1) % space;
}

template<class T>
T& Array_queue<T>::front()
{
	this->check_empty();
	return element[head];
}

template<class T>
const T& Array_queue<T>::front() const
{
	this->check_empty();
	return element[head];
}

template<class T>
T& Array_queue<T>::back()
{
	this->check_empty();
	return element[(tail - 1 + space) % space];
}

template<class T>
const T& Array_queue<T>::back() const
{
	this->check_empty();
	return element[(tail - 1 + space) % space];
}
