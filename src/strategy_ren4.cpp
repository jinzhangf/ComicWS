#include "strategy_ren4.h"

Strategy_Ren4::Strategy_Ren4(int &money, Hot &hot) 
	: _money(money), _hot(hot), _count(0)
{
	//empty
}

Strategy_Ren4::~Strategy_Ren4()
{
	cout << "Strategy_Ren4 stats:" << endl;
	int sum = 0;
	for (auto &item: _table) {
		cout << item.first << " " << item.second << endl;
		sum += item.second;
	}
	double average = 0;
	for (auto &item: _table) {
		average += (double)item.first * (double)item.second / (double)sum;
	}
	cout << "sum:" << sum << endl;
	cout << "average:" << average << endl;
}

vector<OneBet> Strategy_Ren4::make_decision()
{
	stats();

	vector<OneBet> ret;
	return ret;
}

void Strategy_Ren4::stats()
{
	vector<int> last_data = _hot.get_last_data();
	int same_cnt = 0;
	for (auto num : last_data) {
		if (_last_data_set.count(num) > 0) {
			same_cnt++;
		}
	}
	if (same_cnt >= 4) {
		_table[_count]++;
		_count = 0;
	}
	else {
		_count++;
	}

	_last_data_set.clear();
	for (auto num : last_data) {
		_last_data_set.insert(num);
	}
}
