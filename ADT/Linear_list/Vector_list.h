#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include "Linear_list.h"

using std::vector;
using std::invalid_argument;

// ���Ա��vectorʵ��
template<class T>
class Vector_list : public Linear_list<T>
{
protected:
	vector<T> element;	// �洢���Ա�Ԫ�ص�����
public:
	explicit Vector_list(int capacity = 10);

	Vector_list(const Vector_list& v) :element(v.element) {}

	~Vector_list() {}

	bool empty() const override { return element.empty(); }

	int size() const override { return (int) element.size(); }

	const T& get(int index) const override;
	T set(int index, const T& value) override;
	int index_of(const T& value) const override;
	void push_back(const T& value) override;
	void pop_back() override;
	void insert(int index, const T& value) override;
	void erase(int index) override;
	void clear() override;
	void output(ostream& out) const override;

	int capacity() const { return (int) element.capacity(); }

	typedef typename vector<T>::iterator iterator;
	typedef typename vector<T>::const_iterator const_iterator;

	// ����ָ���һ��Ԫ�صĵ�����
	const_iterator begin() const { return element.begin(); }

	// ����ָ�����һ��Ԫ�ص���һ��λ�õĵ�����
	const_iterator end() const { return element.end(); }

	T& operator[](int index) { return element[index]; }

	const T& operator[](int index) const { return element[index]; }

};

// ���캯�������capacity<=0���׳�invalid_argument�쳣
template<class T>
Vector_list<T>::Vector_list(int capacity)
	:element()
{
	if (capacity <= 0) {
		ostringstream oss;
		oss << "initial capacity = " << capacity << ", must be positive";
		throw invalid_argument(oss.str());
	}
	element.reserve(capacity);
}

template<class T>
const T& Vector_list<T>::get(int index) const
{
	this->check_index(index);
	return element[index];
}

template<class T>
T Vector_list<T>::set(int index, const T& value)
{
	this->check_index(index);
	T old = element[index];
	element[index] = value;
	return old;
}

template<class T>
int Vector_list<T>::index_of(const T& value) const
{
	const_iterator p = std::find(element.begin(), element.end(), value);
	return p == element.end() ? -1 : p - element.begin();
}

template<class T>
void Vector_list<T>::push_back(const T& value)
{
	element.push_back(value);
}

template<class T>
void Vector_list<T>::pop_back()
{
	if (element.empty())
		throw out_of_range("pop_back from empty list");
	element.pop_back();
}

template<class T>
void Vector_list<T>::insert(int index, const T& value)
{
	if (index < 0 || index > size()) {
		ostringstream oss;
		oss << "index = " << index << ", size = " << element.size();
		throw out_of_range(oss.str());
	}
	element.insert(element.begin() + index, value);
}

template<class T>
void Vector_list<T>::erase(int index)
{
	this->check_index(index);
	element.erase(element.begin() + index);
}

template<class T>
void Vector_list<T>::clear()
{
	element.clear();
}

template<class T>
void Vector_list<T>::output(ostream& out) const
{
	out << '[';
	copy(element.begin(), element.end() - 1, std::ostream_iterator<T>(out, ", "));
	out << element[element.size() - 1] << ']';
}

template<class T>
ostream& operator<<(ostream& out, const Vector_list<T>& a)
{
	a.output(out);
	return out;
}

template<class T>
bool operator==(const Vector_list<T>& a, const Vector_list<T>& b)
{
	return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

template<class T>
bool operator!=(const Vector_list<T>& a, const Vector_list<T>& b)
{
	return !(a == b);
}

template<class T>
bool operator<(const Vector_list<T>& a, const Vector_list<T>& b)
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}
