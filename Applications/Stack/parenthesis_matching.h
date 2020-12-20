#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;

// 栈的应用：括号匹配
// 输出匹配的括号以及不匹配的括号
void print_matched_parentheses(string expr, ostream& os = std::cout);
