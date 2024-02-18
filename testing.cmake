FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# 添加一个GoogleTest，用法：
# add_gtest(NAME <name> SOURCE <source_file> [LIBRARY <library>...] [GMOCK])
function(add_gtest)
  cmake_parse_arguments("TEST" "GMOCK" "NAME;SOURCE" "LIBRARY" ${ARGN})
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  set(GTEST_LIBRARY $<IF:$<BOOL:${TEST_GMOCK}>,GTest::gmock_main,GTest::gtest_main>)
  target_link_libraries(${TEST_NAME} ${GTEST_LIBRARY} ${TEST_LIBRARY})
  gtest_add_tests(TARGET ${TEST_NAME})
endfunction()
