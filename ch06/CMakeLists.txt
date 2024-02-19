add_library(student student.cpp)

add_gtest(NAME bin_sort_test SOURCE bin_sort_test.cpp LIBRARY student)
add_gtest(NAME radix_sort_test SOURCE radix_sort_test.cpp LIBRARY student)
