#include "bin_sort.h"
#include <vector>

using std::vector;

ostream& operator<<(ostream& out, const Student& s)
{
	out << '(' << s.name << ',' << s.score << ')' << endl;
	return out;
}

void bin_sort(Linked_list<Student>& students, int max_score)
{
	vector<Linked_list<Student> > bins(max_score + 1, Linked_list<Student>());

	// 把学生记录从链表中取出，分配到箱子里
	int n = students.size();
	for (int i = 0; i < n; ++i) {
		Student s = students[0];
		students.erase(0);
		bins[s.score].insert(0, s);
	}

	// 从箱子中收集元素
	for (int i = max_score; i >= 0; --i)
		while (!bins[i].empty()) {
			Student s = bins[i][0];
			bins[i].erase(0);
			students.insert(0, s);
		}
}
