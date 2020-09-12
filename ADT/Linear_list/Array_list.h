#pragma once
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include "Linear_list.h"
#include "../utils.h"

using std::ostringstream;
using std::copy;
using std::invalid_argument;
using std::out_of_range;

// 线性表的数组实现
template<class T>
class Array_list : public Linear_list<T>
{
protected:
	T* element;     // 存储线性表元素的一维数组
	int space;      // 数组的容量
	int sz;         // 元素个数

	// 若index不在[0, sz)内则抛出out_of_range异常
	void check_index(int index) const;
public:
	explicit Array_list(int capacity = 10);
	Array_list(const Array_list& a);

	~Array_list() { delete[] element; }

	Array_list<T>& operator=(const Array_list<T>& a);

	bool empty() const override { return sz == 0; }

	int size() const override { return sz; }

	T& get(int index) const override;
	T set(int index, const T& value) override;
	int index_of(const T& value) const override;
	void push_back(const T& value) override;
	void pop_back() override;
	void erase(int index) override;
	void insert(int index, const T& value) override;
	void output(ostream& out) const override;

	int capacity() const { return space; }

	class iterator
	{
	protected:
		T* position;
	public:
		// C++的双向迭代器需要的typedef
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		explicit iterator(T* p = nullptr) :position(p) {}

		T& operator*() const { return *position; }

		T* operator->() const { return position; }

		iterator& operator++() { ++position; return *this; }

		iterator operator++(int) { return iterator(position++); }

		iterator& operator--() { --position; return *this; }

		iterator operator--(int) { return iterator(position--); }

		bool operator==(const iterator& right) const { return position == right.position; }

		bool operator!=(const iterator& right) const { return position != right.position; }
	};

	// 返回指向第一个元素的迭代器
	iterator begin() const { return iterator(element); }

	// 返回指向最后一个元素的下一个位置的迭代器
	iterator end() const { return iterator(element + sz); }

};

template<class T>
void Array_list<T>::check_index(int index) const
{
	if (index < 0 || index >= sz) {
		ostringstream oss;
		oss << "index = " << index << ", size = " << sz;
		throw out_of_range(oss.str());
	}
}

// 构造函数，如果capacity<=0则抛出invalid_argument异常
template<class T>
Array_list<T>::Array_list(int capacity)
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

// 拷贝构造函数
template<class T>
Array_list<T>::Array_list(const Array_list& a)
{
	space = a.space;
	sz = a.sz;
	element = new T[space];
	copy(a.element, a.element + a.sz, element);
}

// 赋值运算符
template<class T>
Array_list<T>& Array_list<T>::operator=(const Array_list<T>& a)
{
	if (this != &a) {
		delete[] element;
		element = new T[a.space];
		copy(a.element, a.element + a.sz, element);
		space = a.space;
		sz = a.sz;
	}
	return *this;
}

template<class T>
T& Array_list<T>::get(int index) const
{
	check_index(index);
	return element[index];
}

template<class T>
T Array_list<T>::set(int index, const T& value)
{
	check_index(index);
	T old = element[index];
	element[index] = value;
	return old;
}

template<class T>
int Array_list<T>::index_of(const T& value) const
{
	int index = std::find(element, element + sz, value) - element;
	return index == sz ? -1 : index;
}

template<class T>
void Array_list<T>::push_back(const T& value)
{
	if (sz == space) {
		change_length_1d(element, space, 2 * space);
		space *= 2;
	}
	element[sz++] = value;
}

template<class T>
void Array_list<T>::pop_back()
{
	element[--sz].~T();
}

template<class T>
void Array_list<T>::erase(int index)
{
	check_index(index);
	copy(element + index + 1, element + sz, element + index);
	element[--sz].~T();  // 调用析构函数
}

template<class T>
void Array_list<T>::insert(int index, const T& value)
{
	if (index < 0 || index > sz) {   // index可以等于list_size
		ostringstream oss;
		oss << "index = " << index << ", size = " << sz;
		throw out_of_range(oss.str());
	}

	// 确定数组是否已满
	if (sz == space) {
		change_length_1d(element, space, 2 * space);
		space *= 2;
	}

	// 把元素向右移动一个位置
	std::copy_backward(element + index, element + sz, element + sz + 1);
	element[index] = value;
	++sz;
}

template<class T>
void Array_list<T>::output(ostream& out) const
{
	out << '[';
	copy(element, element + sz - 1, std::ostream_iterator<T>(out, ", "));
	out << element[sz - 1] << ']';
}

template<class T>
ostream& operator<<(ostream& out, const Array_list<T>& x)
{
	x.output(out);
	return out;
}
