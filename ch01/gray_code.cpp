#include "gray_code.h"

std::vector<int> gray_code(int n) {
    if (n <= 1) return {1};

    std::vector<int> g = gray_code(n - 1);
    int s = g.size();
    g.push_back(n);
    g.insert(g.end(), g.begin(), g.begin() + s);
    return g;
}
