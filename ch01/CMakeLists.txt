add_library(Currency Currency.cpp)

add_gtest(NAME Currency_test SOURCE Currency_test.cpp LIBRARY Currency)
