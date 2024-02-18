#include "rearranging_railroad_cars.h"
#include "ADT/Stack/Array_stack.h"

using std::endl;

vector<Array_stack<int> > tracks;
int num_cars = 0;
int next_car = 0;
int smallest_car = -1;  // 缓冲轨道中编号最小的车厢
int smallest_track = -1;  // 编号最小的车厢所在的缓冲轨道

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
			// 直接移到出轨道
			os << "car " << input_order[i] << ": input -> output" << endl;
			++next_car;

			// 从缓冲轨道移到出轨道
			while (smallest_car == next_car) {
				output_from_holding_track(os);
				++next_car;
			}
		}
		else {
			// 移到一个缓冲轨道
			if (!put_in_holding_track(input_order[i], os))
				return false;
		}
	return true;
}

// 将编号最小的车厢从缓冲轨道移到出轨道
void output_from_holding_track(ostream& os)
{
	tracks[smallest_track].pop();
	os << "car " << next_car << ": holding track " << smallest_track << " -> output" << endl;
	// 检查所有栈顶，寻找编号最小的车厢和它所属的栈
	smallest_car = 0x7fffffff;
	for (int i = 0; i < tracks.size(); ++i)
		if (!tracks[i].empty() && tracks[i].top() < smallest_car) {
			smallest_car = tracks[i].top();
			smallest_track = i;
		}
}

// 将车厢c移到一个缓冲轨道，如果没有可用的缓冲轨道则返回false，否则返回true
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
