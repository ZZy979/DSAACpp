#pragma once
#include <iostream>
#include <string>
#include "Linear_list/Linked_list.h"

using std::ostream;
using std::endl;
using std::string;

// ���Ա��Ӧ�ã���������

// ѧ����¼
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

// �������򣺽�students����������
void bin_sort(Linked_list<Student>& students, int max_score);
