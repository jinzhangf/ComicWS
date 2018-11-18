#include "strategy_ren1.h"

Strategy_Ren1::Strategy_Ren1(int &money, Hot &hot) 
	: _money(money), _hot(hot), _miss(11, 0)
{
	//empty
}

Strategy_Ren1::~Strategy_Ren1()
{
	cout << "_miss_stats :" << endl;
	for (auto &item : _miss_stats) {
		if (item.first < 50)
			continue;

		cout << item.first << "\t" << item.second << endl;

		for (auto &sub_item : _sec_miss_stats[item.first]) {
			//cout << "---- " << sub_item.first << "\t" << sub_item.second << endl;
		}
	}
	cout << endl;
}


vector<OneBet> Strategy_Ren1::make_decision()
{
	stats();

	//make decision
	vector<OneBet> ret;
	size_t index;
	int cur_max_miss = max_miss(index);
	size_t sec_index;
	int second_max_miss = sec_max_miss(sec_index, index);

	if (second_max_miss == 45) {
		OneBet onebet;
		onebet._play_type = PLAY_ONE_DOUBLE;
		onebet._nums.push_back(index + 1);
		onebet._nums.push_back(sec_index + 1);
		set_bet_money(15, 10, 0.1, onebet);
		ret.push_back(onebet);
		_money -= std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
	}

	/******单高风险大
	if (cur_max_miss == 60) {
		OneBet onebet;
		onebet._play_type = PLAY_ONE;
		onebet._nums.push_back(index + 1);
		set_bet_money(10, 100, 0.3, onebet);
		ret.push_back(onebet);
		_money -= std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
	}
	*************************/

	return ret;
}

int Strategy_Ren1::max_miss(size_t &index)
{
	int max_ret = -1;
	for (size_t i = 0; i < 11; ++i) {
		if (_miss[i] > max_ret) {
			index = i;
			max_ret = _miss[i];
		}
	}
	return max_ret;
}

int Strategy_Ren1::sec_max_miss(size_t &index, int max_miss_index)
{
	int max_ret = -1;
	for (size_t i = 0; i < 11; ++i) {
		if (i == max_miss_index) {
			continue;
		}

		if (_miss[i] > max_ret) {
			index = i;
			max_ret = _miss[i];
		}
	}
	return max_ret;
}

void Strategy_Ren1::stats()
{
	static set<int> _appear_set; // 出现的集合，
	vector<int> last_data = _hot.get_last_data();

	// 全部数字都出现过统计才有意义
	if (_appear_set.size() == 11) {
		size_t index;
		int cur_max_miss = max_miss(index);

		if (index + 1 == last_data[0]) {
			// 本次遗漏加1
			size_t sec_index;
			_miss[index] = 0;
			int second_max_miss = max_miss(sec_index);
			_miss_stats[cur_max_miss + 1]++;
			_sec_miss_stats[cur_max_miss + 1][second_max_miss + 1]++;
		}
	}

	_appear_set.insert(last_data[0]);
	for (size_t i = 0; i < 11; ++i) {
		_miss[i]++;
	}
	_miss[last_data[0] - 1] = 0;
}
