#pragma once
#include <sstream>
#include <stdexcept>
#include <algorithm>

using std::ostringstream;
using std::out_of_range;
using std::invalid_argument;
using std::copy;
using std::fill;
using std::equal;

template<class T>
class Matrix
{
	int r;		// 矩阵的行数
	int c;		// 矩阵的列数
	T* element;	// 矩阵元素

	void check_index(int i, int j) const;
	void check_same_size(const Matrix<T>& m) const;
	void check_mul_size(const Matrix<T>& m) const;
public:
	Matrix(int rows, int columns);
	Matrix(int rows, int columns, int data[]);
	Matrix(const Matrix<T>& m);

	~Matrix() { delete[] element; }

	Matrix<T>& operator=(const Matrix<T>& m);

	int rows() const { return r; }

	int columns() const { return c; }

	const T& operator()(int i, int j) const;
	T& operator()(int i, int j);
	Matrix<T> operator+() const;
	Matrix<T> operator+(const Matrix<T>& m) const;
	Matrix<T> operator-() const;
	Matrix<T> operator-(const Matrix<T>& m) const;
	Matrix<T> operator*(const Matrix<T>& m) const;
	bool operator==(const Matrix<T>& m) const;
	Matrix<T> transpose() const;
};

template<class T>
void Matrix<T>::check_index(int i, int j) const
{
	if (i < 0 || i >= r || j < 0 || j >= c) {
		ostringstream oss;
		oss << "matrix size: (" << r << ',' << c << ')';
		oss << ", index: (" << i << ',' << j << ')';
		throw out_of_range(oss.str());
	}
}

template<class T>
void Matrix<T>::check_same_size(const Matrix<T>& m) const
{
	if (m.r != r || m.c != c) {
		ostringstream oss;
		oss << "matrix sizes mismatch: (" << r << ',' << c << ')';
		oss << " and (" << m.r << ',' << m.c << ')';
		throw invalid_argument(oss.str());
	}
}

template<class T>
void Matrix<T>::check_mul_size(const Matrix<T>& m) const
{
	if (m.r != c) {
		ostringstream oss;
		oss << "matrix sizes mismatch for multiplication: (" << r << ',' << c << ')';
		oss << " and (" << m.r << ',' << m.c << ')';
		throw invalid_argument(oss.str());
	}
}

template<class T>
Matrix<T>::Matrix(int rows, int columns)
{
	if (rows <= 0 || columns <= 0)
		throw invalid_argument("Rows and columns must be >0");
	r = rows;
	c = columns;
	element = new T[rows * columns];
	fill(element, element + rows * columns, T());
}

template<class T>
Matrix<T>::Matrix(int rows, int columns, int data[])
{
	if (rows <= 0 || columns <= 0)
		throw invalid_argument("Rows and columns must be >0");
	r = rows;
	c = columns;
	element = new T[rows * columns];
	copy(data, data + rows * columns, element);
}

// 拷贝构造函数
template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
	:r(m.r), c(m.c), element(new T[m.r * m.c])
{
	copy(m.element, m.element + r * c, element);
}

// 赋值运算符
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
	if (this != &m) {
		delete[] element;
		r = m.r;
		c = m.c;
		element = new T[r * c];
		copy(m.element, m.element + r * c, element);
	}
	return *this;
}

template<class T>
const T& Matrix<T>::operator()(int i, int j) const
{
	check_index(i, j);
	return element[i * c + j];
}

template<class T>
T& Matrix<T>::operator()(int i, int j)
{
	check_index(i, j);
	return element[i * c + j];
}

template<class T>
Matrix<T> Matrix<T>::operator+() const
{
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const
{
	check_same_size(m);
	Matrix<T> sum(r, c);
	for (int i = 0; i < r * c; ++i)
		sum.element[i] = element[i] + m.element[i];
	return sum;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const
{
	Matrix<T> neg(r, c);
	for (int i = 0; i < r * c; ++i)
		neg.element[i] = -element[i];
	return neg;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m) const
{
	check_same_size(m);
	Matrix<T> diff(r, c);
	for (int i = 0; i < r * c; ++i)
		diff.element[i] = element[i] - m.element[i];
	return diff;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const
{
	check_mul_size(m);
	Matrix<T> product(r, m.c);
	int cp = 0;
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < m.c; ++j) {
			// 从*this(i, 0)和m(0, j)开始
			int ct = i * c, cm = j;
			T sum = T();
			for (int k = 0; k < c; ++k) {
				sum += element[ct] * m.element[cm];
				++ct;
				cm += m.c;
			}
			product.element[cp++] = sum;
		}
	return product;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T>& m) const
{
	return r == m.r && c == m.c && equal(element, element + r * c, m.element);
}

template<class T>
Matrix<T> Matrix<T>::transpose() const
{
	Matrix<T> t(c, r);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			t.element[j * r + i] = element[i * c + j];
	return t;
}
