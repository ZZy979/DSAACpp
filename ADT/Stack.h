#pragma once
#include <stdexcept>

using std::out_of_range;

class Stack_empty : public out_of_range
{
public:
	Stack_empty() :out_of_range("Empty Stack") {}
};

// 抽象类Stack，栈ADT
template<class T>
class Stack
{
protected:
	void check_empty() const;
public:
	virtual ~Stack() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void push(const T& value) = 0;
	virtual void pop() = 0;
	virtual T& top() = 0;
	virtual const T& top() const = 0;
	virtual void clear() = 0;
};

template<class T>
void Stack<T>::check_empty() const
{
	if(empty())
		throw Stack_empty();
}
