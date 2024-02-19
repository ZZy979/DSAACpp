#include "student.h"

ostream& operator<<(ostream& out, const Student& s)
{
	out << '(' << s.name << ',' << s.score << ')' << std::endl;
	return out;
}
