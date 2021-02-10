#pragma once
#include <stdexcept>

using std::out_of_range;

class Queue_empty : public out_of_range
{
public:
	Queue_empty() :out_of_range("Empty Queue") {}
};

// 抽象类Queue，队列ADT
template<class T>
class Queue
{
protected:
	void check_empty() const;
public:
	virtual ~Queue() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void push(const T& value) = 0;
	virtual void pop() = 0;
	virtual T& front() = 0;
	virtual const T& front() const = 0;
	virtual T& back() = 0;
	virtual const T& back() const = 0;
	virtual void clear() = 0;
};

template<class T>
void Queue<T>::check_empty() const
{
	if (empty())
		throw Queue_empty();
}
