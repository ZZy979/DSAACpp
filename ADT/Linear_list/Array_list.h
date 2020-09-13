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

// ���Ա������ʵ��
template<class T>
class Array_list : public Linear_list<T>
{
protected:
	T* element;     // �洢���Ա�Ԫ�ص�һά����
	int space;      // ���������
	int sz;         // Ԫ�ظ���

	// ��index����[0, sz)�����׳�out_of_range�쳣
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
		// C++��˫���������Ҫ��typedef
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

	// ����ָ���һ��Ԫ�صĵ�����
	iterator begin() const { return iterator(element); }

	// ����ָ�����һ��Ԫ�ص���һ��λ�õĵ�����
	iterator end() const { return iterator(element + sz); }

	T& operator[](int index) { return element[index]; }

	const T& operator[](int index) const { return element[index]; }

	// ʹ������������max{size(), 1}
	void trim_to_size();

	// ʹ���Ա�Ĵ�С����new_size
	// ���new_size<size()��ɾ������Ԫ�أ�����ʲô������
	void set_size(int new_size);

	// ����value���һ�γ���ʱ�����������������򷵻�-1
	int last_index_of(const T& value) const;

	// ����Ԫ��*this��a��Ԫ��
	void swap(Array_list<T>& a);

	// ������������Ϊ��ǰ������new_capacity�Ľϴ���
	void reserve(int new_capacity);

	// ������Ա�
	void clear();

	// ɾ��[from, to)�ڵ�����Ԫ�أ���from��to����[0, size())�����׳�out_of_range�쳣
	void remove_range(int from, int to);

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

// ���캯�������capacity<=0���׳�invalid_argument�쳣
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

// �������캯��
template<class T>
Array_list<T>::Array_list(const Array_list& a)
{
	space = a.space;
	sz = a.sz;
	element = new T[space];
	copy(a.element, a.element + a.sz, element);
}

// ��ֵ�����
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
	element[--sz].~T();  // ������������
}

template<class T>
void Array_list<T>::insert(int index, const T& value)
{
	if (index < 0 || index > sz) {   // index���Ե���list_size
		ostringstream oss;
		oss << "index = " << index << ", size = " << sz;
		throw out_of_range(oss.str());
	}

	// ȷ�������Ƿ�����
	if (sz == space) {
		change_length_1d(element, space, 2 * space);
		space *= 2;
	}

	// ��Ԫ�������ƶ�һ��λ��
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
ostream& operator<<(ostream& out, const Array_list<T>& a)
{
	a.output(out);
	return out;
}

template<class T>
bool operator==(const Array_list<T>& a, const Array_list<T>& b)
{
	return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

template<class T>
bool operator!=(const Array_list<T>& a, const Array_list<T>& b)
{
	return !(a == b);
}

template<class T>
bool operator<(const Array_list<T>& a, const Array_list<T>& b)
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template<class T>
void Array_list<T>::trim_to_size()
{
	if (space == sz)
		return;
	space = sz == 0 ? 1 : sz;
	change_length_1d(element, sz, space);
}

template<class T>
void Array_list<T>::set_size(int new_size)
{
	while (sz > new_size)
		pop_back();
}

template<class T>
int Array_list<T>::last_index_of(const T& value) const
{
	for (int index = sz - 1; index >= 0; --index)
		if (element[index] == value)
			return index;
	return -1;
}

template<class T>
void Array_list<T>::swap(Array_list<T>& a)
{
	std::swap(element, a.element);
	std::swap(space, a.space);
	std::swap(sz, a.sz);
}

template<class T>
void Array_list<T>::reserve(int new_capacity)
{
	if (new_capacity > space) {
		change_length_1d(element, space, new_capacity);
		space = new_capacity;
	}
}

template<class T>
void Array_list<T>::clear()
{
	while (sz > 0)
		pop_back();
}

template<class T>
void Array_list<T>::remove_range(int from, int to)
{
	check_index(from);
	check_index(to);
	if (from >= to)
		return;
	copy(element + to, element + sz, element + from);
	int new_size = sz - to + from;
	for (int i = new_size; i < sz; ++i)
		element[i].~T();
	sz = new_size;
}
