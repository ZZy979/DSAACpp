#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;

// 学生记录
struct Student
{
	string name;
	int score;

	Student(const string& n, int s) :name(n), score(s) {}

	bool operator==(const Student& s) const { return score == s.score; }

	bool operator!=(const Student& s) const { return score != s.score; }

	operator int() const { return score; }

};

ostream& operator<<(ostream& out, const Student& s);
