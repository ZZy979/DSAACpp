#pragma once
#include <algorithm>
#include <stdexcept>

using std::copy;
using std::min;
using std::invalid_argument;

// �ı�һά����a�ĳ���
// ���new_length<=0���׳�invalid_argument�쳣
template<class T>
void change_length_1d(T*& a, int old_length, int new_length)
{
	if (new_length <= 0)
		throw invalid_argument("new_length must be > 0");
	T* temp = new T[new_length];
	copy(a, a + min(old_length, new_length), temp);
	delete[] a;
	a = temp;
}

// ����һ����ά����
template<class T>
void make_2d_array(T**& a, int n_rows, int n_columns)
{
	// ������ָ��
	a = new T*[n_rows];

	// Ϊÿһ�з���ռ�
	for (int i = 0; i < n_rows; ++i)
		a[i] = new T[n_columns];
}

// ����һ����ά����
template<class T>
void make_2d_array(T**& a, int n_rows, const int n_columns[])
{
	// ������ָ��
	a = new T*[n_rows];

	// Ϊÿһ�з���ռ�
	for (int i = 0; i < n_rows; ++i)
		a[i] = new T[n_columns[i]];
}

// ɾ����ά����a
template<class T>
void delete_2d_array(T**& a, int n_rows)
{
	// ɾ��������ռ�
	for (int i = 0; i < n_rows; ++i)
		delete[] a[i];

	// ɾ����ָ��
	delete[] a;
	a = nullptr;
}

// �ı��ά����a�ĳ���
// ���new_n_rows<=0��new_n_columns<=0���׳�invalid_argument�쳣
template<class T>
void change_length_2d(T**& a, int old_n_rows, int old_n_columns,
	int new_n_rows, int new_n_columns)
{
	if (new_n_rows <= 0 || new_n_columns <= 0)
		throw invalid_argument("new_n_rows and new_n_columns must be > 0");
	T** temp;
	make_2d_array(temp, new_n_rows, new_n_columns);
	for (int i = 0; i < min(old_n_rows, new_n_rows); ++i)
		copy(a[i], a[i] + min(old_n_columns, new_n_columns), temp[i]);
	delete_2d_array(a, old_n_rows);
	a = temp;
}

// �ı��ά����a�ĳ��ȣ�ÿһά�ĳ��ȿ��Բ�ͬ
// ���new_n_rows<=0��new_n_columns[i]<=0���׳�invalid_argument�쳣
template<class T>
void change_length_2d(T**& a, int old_n_rows, const int old_n_columns[],
	int new_n_rows, const int new_n_columns[])
{
	if (new_n_rows <= 0 || std::count_if(new_n_columns, new_n_columns + new_n_rows,
		[](int x) { return x <= 0; }) > 0)
		throw invalid_argument("new_n_rows and new_n_columns must be > 0");
	T** temp;
	make_2d_array(temp, new_n_rows, new_n_columns);
	for (int i = 0; i < min(old_n_rows, new_n_rows); ++i)
		copy(a[i], a[i] + min(old_n_columns[i], new_n_columns[i]), temp[i]);
	delete_2d_array(a, old_n_rows);
	a = temp;
}
