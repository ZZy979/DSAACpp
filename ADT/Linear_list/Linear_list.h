#pragma once
#include <iostream>

using std::ostream;

// ������Linear_list�����Ա�ADT
template<class T>
class Linear_list
{
public:
	virtual ~Linear_list() = default;

	// ����true�����ҽ������Ա�Ϊ��
	virtual bool empty() const = 0;

	// �������Ա��Ԫ�ظ���
	virtual int size() const = 0;

	// ��������Ϊindex��Ԫ�أ���index����[0, size())�����׳�out_of_range�쳣
	virtual T& get(int index) const = 0;

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
