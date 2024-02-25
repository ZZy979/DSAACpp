#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>

// Generate all permutations of a[k:m].
// Assume k <= m.
template<class T>
void permutations(T a[], int k, int m, std::ostream& os) {
    if (k == m) {
        // a[k:m] has one permutation, output it
        std::copy(a, a + m + 1, std::ostream_iterator<T>(os, " "));
        os << std::endl;
    }
    else {
        // a[k:m] has more than one permutation, generate these recursively
        for (int i = k; i <= m; ++i) {
            std::swap(a[k], a[i]);
            permutations(a, k + 1, m, os);
            std::swap(a[k], a[i]);
        }
    }
}
