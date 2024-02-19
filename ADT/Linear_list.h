#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::ostream;
using std::ostringstream;
using std::out_of_range;

// 抽象类Linear_list，线性表ADT
template<class T>
class Linear_list
{
protected:
	// 若index不在[0, size())内则抛出out_of_range异常
	void check_index(int index) const;
public:
	virtual ~Linear_list() = default;

	// 返回true，当且仅当线性表为空
	virtual bool empty() const = 0;

	// 返回线性表的元素个数
	virtual int size() const = 0;

	// 返回索引为index的元素，若index不在[0, size())内则抛出out_of_range异常
	virtual const T& get(int index) const = 0;

	// 用value替换索引为index的元素并返回原来的元素
	// 若index不在[0, size())内则抛出out_of_range异常
	virtual T set(int index, const T& value) = 0;

	// 返回value第一次出现时的索引，若不存在则返回-1
	virtual int index_of(const T& value) const = 0;

	// 把value插入线性表的右端
	virtual void push_back(const T& value) = 0;

	// 把线性表右端的元素删除，如果表为空则抛出out_of_range异常
	virtual void pop_back() = 0;

	// 把value插入索引为index的位置上，若index不在[0, size()]内则抛出out_of_range异常
	virtual void insert(int index, const T& value) = 0;

	// 删除索引为index的元素，若index不在[0, size())内则抛出out_of_range异常
	virtual void erase(int index) = 0;

	// 清空线性表
	virtual void clear() = 0;

	// 把线性表插入输出流out
	virtual void output(ostream& out) const = 0;
};

template<class T>
void Linear_list<T>::check_index(int index) const
{
	if (index < 0 || index >= size()) {
		ostringstream oss;
		oss << "index = " << index << ", size = " << size();
		throw out_of_range(oss.str());
	}
}
