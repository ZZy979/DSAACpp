#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::ostream;
using std::ostringstream;
using std::out_of_range;

// ������Linear_list�����Ա�ADT
template<class T>
class Linear_list
{
protected:
	// ��index����[0, size())�����׳�out_of_range�쳣
	void check_index(int index) const;
public:
	virtual ~Linear_list() = default;

	// ����true�����ҽ������Ա�Ϊ��
	virtual bool empty() const = 0;

	// �������Ա��Ԫ�ظ���
	virtual int size() const = 0;

	// ��������Ϊindex��Ԫ�أ���index����[0, size())�����׳�out_of_range�쳣
	virtual const T& get(int index) const = 0;

	// ��value�滻����Ϊindex��Ԫ�ز�����ԭ����Ԫ��
	// ��index����[0, size())�����׳�out_of_range�쳣
	virtual T set(int index, const T& value) = 0;

	// ����value��һ�γ���ʱ�����������������򷵻�-1
	virtual int index_of(const T& value) const = 0;

	// ��value�������Ա���Ҷ�
	virtual void push_back(const T& value) = 0;

	// �����Ա��Ҷ˵�Ԫ��ɾ��
	virtual void pop_back() = 0;

	// ɾ������Ϊindex��Ԫ�أ���index����[0, size())�����׳�out_of_range�쳣
	virtual void erase(int index) = 0;

	// ��value��������Ϊindex��λ���ϣ���index����[0, size()]�����׳�out_of_range�쳣
	virtual void insert(int index, const T& value) = 0;

	// �����Ա���������out
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
