#include "strategy_ren8.h"

Strategy_Ren8::Strategy_Ren8(int &money, Hot &hot) 
	: _money(money), _hot(hot)
{
	//empty
}

Strategy_Ren8::~Strategy_Ren8()
{
	cout << "_win_table:" << endl;
	for (auto &item : _win_table) {
		cout << item.first << ":" << item.second << endl;
	}
	cout << "_lose_table:" << endl;
	for (auto &item : _lose_table) {
		cout << item.first << ":" << item.second << endl;
	}
}

struct CmpInfo
{
	int num;
	int val;
};

static bool cmp_hot(CmpInfo a, CmpInfo b)
{
	return a.val > b.val;
}

template<typename T>
static void display_cmpInfo(T head, const vector<CmpInfo> &info)
{
	cout << head << ":" ;
	for (auto item : info) {
		cout << item.num << "(" << item.val << ") ";
	}
	cout << endl;
}

static vector<vector<CmpInfo>> get_sorted_hot_rel(Hot &_hot)
{
	vector<vector<CmpInfo>> ret;
	vector<vector<int>> hot_rel = _hot.get_hot_rel_two({5, 10, 30});
	for (size_t i = 0; i < 11; ++i) {
		vector<CmpInfo> line;
		for (size_t j = 0; j < 11; ++j) {
			CmpInfo info;
			info.num = j + 1;
			info.val = hot_rel[i][j];
			line.push_back(info);
		}
		sort(line.begin(), line.end(), cmp_hot);
		display_cmpInfo(i+1, line);
		ret.push_back(line);
	}
	return ret;
}

static int get_hot_paired(int num, vector<vector<CmpInfo>> &sorted_hot_rel, set<int> &last_data_set)
{
	auto sorted_hot_rel_line = sorted_hot_rel[num - 1];
	int ret = 0;
	for (auto &item : sorted_hot_rel_line) {
		if (last_data_set.count(item.num)) {
			ret = item.num;
			break;
		}
	}
	return ret;
}

vector<OneBet> Strategy_Ren8::make_decision()
{
	stats();
	vector<OneBet> ret;
	if (_hot.get_size() < 30) return ret;

	vector<int> last_data = _hot.get_last_data();
	set<int> last_data_set(last_data.begin(), last_data.end());
	vector<int> hot_data = _hot.get_hot_data({5, 10, 30});
	vector<CmpInfo> hot_sorted_last_data;
	for (int num = 1; num < 11; ++num) {
		CmpInfo info;
		info.num = num;
		info.val = hot_data[num - 1];
		hot_sorted_last_data.push_back(info);
	}
	sort(hot_sorted_last_data.begin(), hot_sorted_last_data.end(), cmp_hot);
	/*
	for (size_t i = 8; i < 11; ++i) {
		if (last_data_set.count(hot_sorted_last_data[i].num) > 0) {
			return ret;
		}
	}
	*/

	display_cmpInfo("hot", hot_sorted_last_data);
	
	OneBet onebet;
	onebet._play_type = PLAY_EIGHT;
	for (size_t i = 0; i < 8; ++i) {
		onebet._nums.push_back(hot_sorted_last_data[i].num);
	}
	set_bet_money(1, 1, onebet);
	//set_bet_money(9, 1, 0.3, onebet);
	//_money -= std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
	ret.push_back(onebet);

	return ret;
}

void Strategy_Ren8::stats()
{
}

void Strategy_Ren8::win_or_not(bool state)
{
	static bool first_time = true;
	if (first_time) {
		_last_state = state;
		_state_cnt = 1;
		first_time = false;
		return;
	}

	if (state == _last_state) {
		_state_cnt++;
	}
	else {
		if (_last_state) { //win
			_win_table[_state_cnt]++;
		}
		else { //lose
			_lose_table[_state_cnt]++;			
		}
		_state_cnt = 1;
		_last_state = state;
	}
}
