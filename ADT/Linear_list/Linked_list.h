#pragma once
#include "Linear_list.h"
#include "List_node.h"

// ����ͷ�ڵ�ĵ�������
template<class T>
class Linked_list : public Linear_list<T>
{
protected:
	List_node<T>* first;	// ָ���һ���ڵ��ָ��
	List_node<T>* last;		// ָ�����һ���ڵ��ָ��
	int sz;                 // Ԫ�ظ���
private:
	void copy(const Linked_list<T>& l);
public:
	Linked_list() :first(nullptr), last(nullptr), sz(0) {}

	Linked_list(const Linked_list<T>& l);
	~Linked_list();
	Linked_list<T>& operator=(const Linked_list<T>& l);

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
		// C++��ǰ���������Ҫ��typedef
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

	// ����ָ���һ��Ԫ�صĵ�����
	iterator begin() const { return iterator(first); }

	// ����ָ�����һ��Ԫ�ص���һ��λ�õĵ�����
	iterator end() const { return iterator(nullptr); }

	T& operator[](int index);

	const T& operator[](int index) const { return get(index); }

	// ʹ���Ա�Ĵ�С����new_size
	// ���new_size<size()��ɾ������Ԫ�أ�����ʲô������
	void set_size(int new_size);

	// ����value���һ�γ���ʱ�����������������򷵻�-1
	int last_index_of(const T& value) const;

	// ����Ԫ��*this��l��Ԫ��
	void swap(Linked_list<T>& l);

	// ɾ��[from, to)�ڵ�����Ԫ�أ���from��to����[0, size())�����׳�out_of_range�쳣
	void remove_range(int from, int to);

};

template<class T>
void Linked_list<T>::copy(const Linked_list<T>& l)
{
	sz = l.sz;
	if (sz == 0) {
		first = last = nullptr;
		return;
	}
	List_node<T>* from = l.first;
	first = new List_node<T>(from->value);
	from = from->next;
	List_node<T>* to = first;
	while (from) {
		to->next = new List_node<T>(from->value);
		from = from->next;
		to = to->next;
	}
	last = to;
}

template<class T>
Linked_list<T>::Linked_list(const Linked_list<T>& l)
{
	copy(l);
}

// ����������ɾ�����нڵ�
template<class T>
Linked_list<T>::~Linked_list()
{
	clear();
}

// ��ֵ�����
template<class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T>& l)
{
	if (this != &l) {
		clear();
		copy(l);
	}
	return *this;
}

template<class T>
const T& Linked_list<T>::get(int index) const
{
	check_index(index);
	List_node<T>* p = first;
	for (int i = 0; i < index; ++i)
		p = p->next;
	return p->value;
}

template<class T>
T Linked_list<T>::set(int index, const T& value)
{
	check_index(index);
	List_node<T>* p = first;
	for (int i = 0; i < index; ++i)
		p = p->next;
	T old = p->value;
	p->value = value;
	return old;
}

template<class T>
int Linked_list<T>::index_of(const T& value) const
{
	List_node<T>* p = first;
	int index = 0;
	while (p && p->value != value) {
		p = p->next;
		++index;
	}
	return p ? index : -1;
}

template<class T>
void Linked_list<T>::push_back(const T& value)
{
	List_node<T>* new_node = new List_node<T>(value);
	if (!first)
		first = last = new_node;
	else
	last = last->next = new_node;
	++sz;
}

template<class T>
void Linked_list<T>::pop_back()
{
	if (sz == 0)
		throw out_of_range("pop_back from empty list");
	List_node<T>* node = last;
	if (sz == 1)
		first = last = nullptr;
	else {
		List_node<T>* p = first;
		while (p->next != last)
			p = p->next;
		last = p;
		last->next = nullptr;
	}
	delete node;
	--sz;
}

template<class T>
void Linked_list<T>::insert(int index, const T& value)
{
	if (index < 0 || index > sz) {
		ostringstream oss;
		oss << "index = " << index << ", size = " << sz;
		throw out_of_range(oss.str());
	}
	if (index == 0) {
		first = new List_node<T>(value, first);
		if (sz == 0)
			last = first;
	}
	else if (index == sz)
		push_back(value);
	else {
		// �ҵ���Ԫ�ص�ǰ���ڵ�
		List_node<T>* p = first;
		for (int i = 0; i < index - 1; ++i)
			p = p->next;
		p->next = new List_node<T>(value, p->next);
	}
	++sz;
}

template<class T>
void Linked_list<T>::erase(int index)
{
	check_index(index);
	List_node<T>* delete_node;
	if (index == 0) {
		delete_node = first;
		first = first->next;
		if (sz == 1)
			last = nullptr;
	}
	else {
		// �ҵ���ɾ��Ԫ�ص�ǰ���ڵ�
		List_node<T>* p = first;
		for (int i = 0; i < index - 1; ++i)
			p = p->next;
		delete_node = p->next;
		p->next = p->next->next;
		if (index == sz - 1)
			last = p;
	}
	delete delete_node;
	--sz;
}

template<class T>
void Linked_list<T>::clear()
{
	while (first) {
		List_node<T>* next = first->next;
		delete first;
		first = next;
	}
	last = nullptr;
	sz = 0;
}

template<class T>
void Linked_list<T>::output(ostream& out) const
{
	out << '[';
	for (List_node<T>* p = first; p; p = p->next) {
		out << p->value;
		if (p->next)
			out << ", ";
	}
	out << ']';
}

template<class T>
ostream& operator<<(ostream& out, const Linked_list<T>& a)
{
	a.output(out);
	return out;
}

template<class T>
bool operator==(const Linked_list<T>& a, const Linked_list<T>& b)
{
	return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

template<class T>
bool operator!=(const Linked_list<T>& a, const Linked_list<T>& b)
{
	return !(a == b);
}

template<class T>
bool operator<(const Linked_list<T>& a, const Linked_list<T>& b)
{
	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template<class T>
T& Linked_list<T>::operator[](int index)
{
	check_index(index);
	List_node<T>* p = first;
	for (int i = 0; i < index; ++i)
		p = p->next;
	return p->value;
}

template<class T>
void Linked_list<T>::set_size(int new_size)
{
	if (new_size >= sz)
		return;
	else if (new_size <= 0)
		clear();
	else {
		List_node<T>* new_last = first;
		for (int i = 0; i < new_size - 1; ++i)
			new_last = new_last->next;
		while (new_last->next) {
			List_node<T>* next = new_last->next;
			new_last->next = new_last->next->next;
			delete next;
		}
		last = new_last;
		sz = new_size;
	}
}

template<class T>
int Linked_list<T>::last_index_of(const T& value) const
{
	int index = -1, i = 0;
	for (List_node<T>* p = first; p; p = p->next, ++i)
		if (p->value == value)
			index = i;
	return index;
}

template<class T>
void Linked_list<T>::swap(Linked_list<T>& l)
{
	std::swap(first, l.first);
	std::swap(last, l.last);
	std::swap(sz, l.sz);
}

template<class T>
void Linked_list<T>::remove_range(int from, int to)
{
	check_index(from);
	check_index(to);
	if (from >= to)
		return;
	if (from == 0) {
		for (int i = 0; i < to; ++i) {
			List_node<T>* next = first->next;
			delete first;
			first = next;
		}
		if (to == sz)
			last = nullptr;
	}
	else {
		List_node<T>* p = first;
		for (int i = 0; i < from - 1; ++i)
			p = p->next;
		for (int i = 0; i < to - from; ++i) {
			List_node<T>* next = p->next;
			p->next = p->next->next;
			delete next;
		}
		if (to == sz)
			last = p;
	}
	sz -= to - from;
}
