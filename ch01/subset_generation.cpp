#include "subset_generation.h"

#include <algorithm>
#include <iterator>

void subset(int a[], int k, int n, std::ostream& os) {
    if (k == n) {
        std::copy(a, a + n, std::ostream_iterator<int>(os, " "));
        os << std::endl;
    }
    else {
        a[k] = 0;
        subset(a, k + 1, n, os);
        a[k] = 1;
        subset(a, k + 1, n, os);
    }
}
