#pragma once
#include <iostream>
#include <vector>

using std::ostream;
using std::vector;

// ջ��Ӧ�ã��г���������
// �����ʼ˳��Ϊinput_order�����������Ϊnum_tracks������ƶ�����
// ����ܹ���ɳ���������򷵻�true
bool railroad(vector<int> input_order, int num_tracks, ostream& os = std::cout);
