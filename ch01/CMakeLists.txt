add_library(Currency Currency.cpp)
add_library(subset_generation subset_generation.cpp)
add_library(gray_code gray_code.cpp)

add_gtest(NAME Currency_test SOURCE Currency_test.cpp LIBRARY Currency)
add_gtest(NAME permutations_test SOURCE permutations_test.cpp)
add_gtest(NAME subset_generation_test SOURCE subset_generation_test.cpp LIBRARY subset_generation)
add_gtest(NAME gray_code_test SOURCE gray_code_test.cpp LIBRARY gray_code)
