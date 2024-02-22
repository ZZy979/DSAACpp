#pragma once

#include <algorithm>
#include <stdexcept>

/**
 * Change the length of array a
 *
 * @throws std::invalid_argument if new_length <= 0
 */
template<class T>
void change_length_1d(T*& a, int old_length, int new_length) {
    if (new_length <= 0)
        throw std::invalid_argument("new_length must be > 0");
    T* temp = new T[new_length];
    std::copy(a, a + std::min(old_length, new_length), temp);
    delete[] a;
    a = temp;
}

// Create a two-dimensional array.
template<class T>
void make_2d_array(T**& a, int n_rows, int n_columns) {
    // create pointers for the rows
    a = new T*[n_rows];

    // get memory for each row
    for (int i = 0; i < n_rows; ++i)
        a[i] = new T[n_columns];
}

// Create a two-dimensional array
template<class T>
void make_2d_array(T**& a, int n_rows, const int n_columns[]) {
    // create pointers for the rows
    a = new T*[n_rows];

    // get memory for each row
    for (int i = 0; i < n_rows; ++i)
        a[i] = new T[n_columns[i]];
}

// Delete the two-dimensional array a
template<class T>
void delete_2d_array(T**& a, int n_rows) {
    // delete the memory for each row
    for (int i = 0; i < n_rows; ++i)
        delete[] a[i];

    // delete the row pointers
    delete[] a;
    a = nullptr;
}

/**
 * Change the length of two-dimensional array a
 *
 * @throws std::invalid_argument if new_n_rows <= 0 or new_n_columns <= 0
 */
template<class T>
void change_length_2d(T**& a, int old_n_rows, int old_n_columns, int new_n_rows, int new_n_columns) {
    if (new_n_rows <= 0 || new_n_columns <= 0)
        throw std::invalid_argument("new_n_rows and new_n_columns must be > 0");
    T** temp;
    make_2d_array(temp, new_n_rows, new_n_columns);
    for (int i = 0; i < std::min(old_n_rows, new_n_rows); ++i)
        std::copy(a[i], a[i] + std::min(old_n_columns, new_n_columns), temp[i]);
    delete_2d_array(a, old_n_rows);
    a = temp;
}

/**
 * Change the length of two-dimensional array a
 *
 * @throws std::invalid_argument if new_n_rows <= 0 or new_n_columns[i] <= 0
 */
template<class T>
void change_length_2d(T**& a, int old_n_rows, const int old_n_columns[], int new_n_rows, const int new_n_columns[]) {
    if (new_n_rows <= 0 || std::any_of(new_n_columns, new_n_columns + new_n_rows, [](int x) { return x <= 0; }))
        throw std::invalid_argument("new_n_rows and new_n_columns must be > 0");
    T** temp;
    make_2d_array(temp, new_n_rows, new_n_columns);
    for (int i = 0; i < std::min(old_n_rows, new_n_rows); ++i)
        std::copy(a[i], a[i] + std::min(old_n_columns[i], new_n_columns[i]), temp[i]);
    delete_2d_array(a, old_n_rows);
    a = temp;
}
