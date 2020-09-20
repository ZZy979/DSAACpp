#pragma once
#include "Linear_list.h"
#include "List_node.h"

// 带头节点的单向循环链表
template <class T>
class Circular_linked_list : public Linear_list<T>
{
protected:
	List_node<T>* header;	// 指向头节点的指针
	int sz;
private:
	void copy(const Circular_linked_list<T>& l);
public:
	Circular_linked_list() :header(new List_node<T>()), sz(0) { header->next = header; }

	Circular_linked_list(const Circular_linked_list& l);
	~Circular_linked_list();
	Circular_linked_list<T>& operator=(const Circular_linked_list<T>& l);

	bool empty() const override { return sz == 0; }

	int size() const override { return sz; }

	const T& get(int index) const override;
	T set(int index, const T& value) override;
	int index_of(const T& value) const override;
	void push_back(const T& value) override;
	void pop_back() override;
	void insert(int index, const T& value) override;
	void erase(int index) override;
	void clear() override;
	void output(ostream& out) const override;

	class iterator
	{
	protected:
		List_node<T>* ptr;
	public:
		// C++的前向迭代器需要的typedef
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		explicit iterator(List_node<T>* p) :ptr(p) {}

		T& operator*() const { return ptr->value; }

		T* operator->() const { return &ptr->value; }

		iterator& operator++() { ptr = ptr->next; return *this; }

		iterator operator++(int)
		{
			iterator old = *this;
			ptr = ptr->next;
			return old;
		}

		bool operator==(const iterator& right) const { return ptr == right.ptr; }

		bool operator!=(const iterator& right) const { return ptr != right.ptr; }
	};

	// 返回指向第一个元素的迭代器
	iterator begin() const { return iterator(header->next); }

	// 返回指向最后一个元素的下一个位置的迭代器
	iterator end() const { return iterator(header); }

	T& operator[](int index);

	const T& operator[](int index) const { return get(index); }

	// 使线性表的大小等于new_size
	// 如果new_size<size()则删除多余元素，否则什么都不做
	void set_size(int new_size);

	// 返回value最后一次出现时的索引，若不存在则返回-1
	int last_index_of(const T& value) const;

	// 交换元素*this和l的元素
	void swap(Circular_linked_list<T>& l);

	// 删除[from, to)内的所有元素，若from或to不在[0, size())内则抛出out_of_range异常
	void remove_range(int from, int to);
};

template<class T>
void Circular_linked_list<T>::copy(const Circular_linked_list<T>& l)
{
	sz = l.sz;
	List_node<T>* from = l.header, * to = header;
	while (from->next != l.header) {
		to->next = new List_node<T>(from->next->value);
		from = from->next;
		to = to->next;
	}
	to->next = header;
}

template<class T>
Circular_linked_list<T>::Circular_linked_list(const Circular_linked_list& l)
	:header(new List_node<T>())
{
	copy(l);
}

// 析构函数，删除所有节点
template<class T>
Circular_linked_list<T>::~Circular_linked_list()
{
	clear();
	delete header;
}

// 赋值运算符
template<class T>
Circular_linked_list<T>& Circular_linked_list<T>::operator=(const Circular_linked_list<T>& l)
{
	if (this != &l) {
		clear();
		copy(l);
	}
	return *this;
}

template<class T>
const T& Circular_linked_list<T>::get(int index) const
{
	check_index(index);
	List_node<T>* p = header->next;
	for (int i = 0; i < index; ++i)
		p = p->next;
	return p->value;
}

template<class T>
T Circular_linked_list<T>::set(int index, const T& value)
{
	check_index(index);
	List_node<T>* p = header->next;
	for (int i = 0; i < index; ++i)
		p = p->next;
	T old = p->value;
	p->value = value;
	return old;
}

template<class T>
int Circular_linked_list<T>::index_of(const T& value) const
{
	// 将元素value放入头节点
	header->value = value;
	List_node<T>* p = header->next;
	int index = 0;
	while (p->value != value) {
		p = p->next;
		++index;
	}
	return p == header ? -1 : index;
}

template<class T>
void Circular_linked_list<T>::push_back(const T& value)
{
	header->value = value;
	header = header->next = new List_node<T>(T(), header->next);
	++sz;
}

template<class T>
void Circular_linked_list<T>::pop_back()
{
	if (sz == 0)
		throw out_of_range("pop_back from empty list");
	erase(sz - 1);
}

template<class T>
void Circular_linked_list<T>::insert(int index, const T& value)
{
	if (index < 0 || index > sz) {
		ostringstream oss;
		oss << "index = " << index << ", size = " << sz;
		throw out_of_range(oss.str());
	}
	List_node<T>* p = header;
	for (int i = 0; i < index; ++i)
		p = p->next;
	p->next = new List_node<T>(value, p->next);
	++sz;
}

template<class T>
void Circular_linked_list<T>::erase(int index)
{
	check_index(index);
	List_node<T>* p = header;
	for (int i = 0; i < index; ++i)
		p = p->next;
	List_node<T>* delete_node = p->next;
	p->next = p->next->next;
	delete delete_node;
	--sz;
}

template<class T>
void Circular_linked_list<T>::clear()
{
	while (header->next != header) {
		List_node<T>* next = header->next->next;
		delete header->next;
		header->next = next;
	}
	sz = 0;
}

template<class T>
void Circular_linked_list<T>::output(ostream& out) const
{
	out << '[';
	for (List_node<T>* p = header->next; p != header; p = p->next) {
		out << p->value;
		if (p->next != header)
			out << ", ";
	}
	out << ']';
}

template<class T>
ostream& operator<<(ostream& out, const Circular_linked_list<T>& a)
{
	a.output(out);
	return out;
}

template<class T>
bool operator==(const Circular_linked_list<T>& a, const Circular_linked_list<T>& b)
{
	return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

template<class T>
bool operator!=(const Circular_linked_list<T>& a, const Circular_linked_list<T>& b)
{
	return !(a == b);
}

template<class T>
bool operator<(const Circular_linked_list<T>& a, const Circular_linked_list<T>& b)
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template<class T>
T& Circular_linked_list<T>::operator[](int index)
{
	check_index(index);
	List_node<T>* p = header->next;
	for (int i = 0; i < index; ++i)
		p = p->next;
	return p->value;
}

template<class T>
void Circular_linked_list<T>::set_size(int new_size)
{
	if (new_size >= sz)
		return;
	else if (new_size <= 0)
		clear();
	else {
		List_node<T>* new_last = header;
		for (int i = 0; i < new_size; ++i)
			new_last = new_last->next;
		while (new_last->next != header) {
			List_node<T>* next = new_last->next;
			new_last->next = new_last->next->next;
			delete next;
		}
		sz = new_size;
	}
}

template<class T>
int Circular_linked_list<T>::last_index_of(const T& value) const
{
	int index = -1, i = 0;
	for (List_node<T>* p = header->next; p != header; p = p->next, ++i)
		if (p->value == value)
			index = i;
	return index;
}

template<class T>
void Circular_linked_list<T>::swap(Circular_linked_list<T>& l)
{
	std::swap(header, l.header);
	std::swap(sz, l.sz);
}

template<class T>
void Circular_linked_list<T>::remove_range(int from, int to)
{
	check_index(from);
	check_index(to);
	if (from >= to)
		return;
	List_node<T>* p = header;
	for (int i = 0; i < from; ++i)
		p = p->next;
	for (int i = 0; i < to - from; ++i) {
		List_node<T>* next = p->next;
		p->next = p->next->next;
		delete next;
	}
	sz -= to - from;
}
