#include "rearranging_railroad_cars.h"
#include "Stack/Array_stack.h"

using std::endl;

vector<Array_stack<int> > tracks;
int num_cars = 0;
int next_car = 0;
int smallest_car = -1;  // �������б����С�ĳ���
int smallest_track = -1;  // �����С�ĳ������ڵĻ�����

void output_from_holding_track(ostream& os);
bool put_in_holding_track(int c, ostream& os);

bool railroad(vector<int> input_order, int num_tracks, ostream& os)
{
	tracks.clear();
	tracks.resize(num_tracks);
	num_cars = input_order.size();
	next_car = 0;
	smallest_car = input_order.size();
	smallest_track = -1;
	for (int i = 0; i < input_order.size(); ++i)
		if (input_order[i] == next_car) {
			// ֱ���Ƶ������
			os << "car " << input_order[i] << ": input -> output" << endl;
			++next_car;

			// �ӻ������Ƶ������
			while (smallest_car == next_car) {
				output_from_holding_track(os);
				++next_car;
			}
		}
		else {
			// �Ƶ�һ��������
			if (!put_in_holding_track(input_order[i], os))
				return false;
		}
	return true;
}

// �������С�ĳ���ӻ������Ƶ������
void output_from_holding_track(ostream& os)
{
	tracks[smallest_track].pop();
	os << "car " << next_car << ": holding track " << smallest_track << " -> output" << endl;
	// �������ջ����Ѱ�ұ����С�ĳ������������ջ
	smallest_car = 0x7fffffff;
	for (int i = 0; i < tracks.size(); ++i)
		if (!tracks[i].empty() && tracks[i].top() < smallest_car) {
			smallest_car = tracks[i].top();
			smallest_track = i;
		}
}

// ������c�Ƶ�һ�������������û�п��õĻ������򷵻�false�����򷵻�true
bool put_in_holding_track(int c, ostream& os)
{
	int best_track = -1, best_top = num_cars;
	for (int i = 0; i < tracks.size(); ++i)
		if (!tracks[i].empty()) {
			int top = tracks[i].top();
			if (c < top && top < best_top) {
				best_top = top;
				best_track = i;
			}
		}
		else if (best_track == -1)
			best_track = i;
	if (best_track == -1)
		return false;

	tracks[best_track].push(c);
	os << "car " << c << ": input -> holding track " << best_track << endl;
	if (c < smallest_car) {
		smallest_car = c;
		smallest_track = best_track;
	}
	return true;
}
