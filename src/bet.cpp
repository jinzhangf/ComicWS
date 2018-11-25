#include "bet.h"
#include "strategy1.h"
#include "strategy_ren1.h"
#include "strategy_ren2.h"
#include "strategy_ren3.h"
#include "strategy_ren4.h"
#include "strategy_ren8.h"

static map<int, int> g_table;

Bet::Bet(Hot &hot) : _hot(hot)
{
	// empty
	_money = INIT_MONEY;
	_stg1 = new Strategy1(_money, _hot);
	_stg_ren1 = new Strategy_Ren1(_money, _hot);
	_stg_ren2 = new Strategy_Ren2(_money, _hot);
	_stg_ren3 = new Strategy_Ren3(_money, _hot);
	_stg_ren4 = new Strategy_Ren4(_money, _hot);
	_stg_ren8 = new Strategy_Ren8(_money, _hot);
}

Bet::~Bet()
{
	delete _stg1;
	delete _stg_ren1;
	delete _stg_ren2;
	delete _stg_ren3;
	delete _stg_ren4;
	delete _stg_ren8;

	cout << "_money:" << _money << endl;
	for (auto &onebet : _all_bets) {
		for (auto m : onebet._money) {
			_money += m;
		}
	}
	cout << "_money:" << _money << endl;
	cout << "table:" << endl;
	for (auto &item : g_table) {
		cout << item.first << ":" << item.second << endl;
	}
}

void Bet::bet()
{
	cal_last_bet();
	//vector<OneBet> bets = _stg1->make_decision();
	//_all_bets.insert(_all_bets.end(), bets.begin(), bets.end());

	//vector<OneBet> bets_stg_ren1 = _stg_ren1->make_decision();
	//_all_bets.insert(_all_bets.end(), bets_stg_ren1.begin(), bets_stg_ren1.end());

	//vector<OneBet> bets_stg_ren2 = _stg_ren2->make_decision();
	//_all_bets.insert(_all_bets.end(), bets_stg_ren2.begin(), bets_stg_ren2.end());

/*
	vector<OneBet> bets_stg_ren3 = _stg_ren3->make_decision();
	if (_all_bets.empty()) {
		_all_bets.insert(_all_bets.end(), bets_stg_ren3.begin(), bets_stg_ren3.end());
		for (auto &onebet : bets_stg_ren3) {
			_money -= std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
		}
	}
	*/
	

	//vector<OneBet> bets_stg_ren4 = _stg_ren4->make_decision();
	//_all_bets.insert(_all_bets.end(), bets_stg_ren4.begin(), bets_stg_ren4.end());

	vector<OneBet> bets_stg_ren8 = _stg_ren8->make_decision();
	if (_all_bets.empty()) {
		_all_bets.insert(_all_bets.end(), bets_stg_ren8.begin(), bets_stg_ren8.end());
		for (auto &onebet : bets_stg_ren8) {
			_money -= std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
		}
	}
}

inline bool check_one_bet(const OneBet & one_bet)
{
	/*
	if ((size_t)one_bet._play_type != one_bet._nums.size()) {
		cerr << "Error: PlayType:" << one_bet._play_type 
		     << ", nums.size=" << one_bet._nums.size() << endl;
		exit(1);
	}
	*/
	return true;
}

void Bet::display_one_bet(bool won, const OneBet &one_bet)
{
	_stg_ren8->win_or_not(won);
	g_table[one_bet._index]++;

	cout << "won:" << won << " ";
	cout << "type:"<< one_bet._play_type << " ";
	cout << "_index:"<< one_bet._index << " ";
	cout << "nums:";
	for (auto num : one_bet._nums) {
		cout << num;
		if (num != one_bet._nums.back()) {
			cout << ",";
		}
	}
	cout << " ";
	//cout << "hot_score:" << one_bet._hot_score << " ";
	//cout << "rel_score:" << one_bet._rel_score << " ";
	cout << "m:" << _money;
	cout << endl;
}

void Bet::win_money(const OneBet &one_bet)
{
	int win_m = one_bet._money[one_bet._index] * one_bet._price;
	_money += win_m;
	for (size_t i = one_bet._index + 1; i < one_bet._money.size(); ++i) {
		_money += one_bet._money[i];
	}
}

void Bet::cal_last_bet()
{
	vector<int> last_data = _hot.get_last_data();
	set<int> last_data_set(last_data.begin(), last_data.end());

	vector<OneBet> tmpBets;
	for (auto &one_bet : _all_bets) {
		if (!check_one_bet(one_bet)) continue;
		bool won = false;

		if (one_bet._play_type == PLAY_ONE) {
			if (one_bet._nums.front() == last_data.front()) {
				win_money(one_bet);
				won = true; 
			}
			else {
				one_bet._index++;
			}
		}
		else if (one_bet._play_type == PLAY_ONE_ANY) {
			if (last_data_set.count(one_bet._nums.front()) > 0) {
				win_money(one_bet);
				won = true;
			}
			else {
				one_bet._index++;
			}
		}
		else if (one_bet._play_type == PLAY_ONE_DOUBLE) {
			if (one_bet._nums.front() == last_data.front() ||
				one_bet._nums.back() == last_data.front()) {
				win_money(one_bet);
				won = true;
			}
			else {
				one_bet._index++;
			}
		}
		else if (one_bet._play_type == PLAY_TWO) {
			if (last_data_set.count(one_bet._nums[0]) && 
				last_data_set.count(one_bet._nums[1])) {
				win_money(one_bet);
				won = true;
			}
			else {
				one_bet._index++;
			}
		}
		else if (one_bet._play_type == PLAY_THREE) {
			if (last_data_set.count(one_bet._nums[0]) && 
				last_data_set.count(one_bet._nums[1]) && 
				last_data_set.count(one_bet._nums[2])) {
				win_money(one_bet);
				won = true;
			}
			else {
				one_bet._index++;
				
			}
		}
		else if (one_bet._play_type == PLAY_EIGHT) {
			set<int> nums_set(one_bet._nums.begin(), one_bet._nums.end());
			if (nums_set.count(last_data[0]) && 
				nums_set.count(last_data[1]) && 
				nums_set.count(last_data[2]) && 
				nums_set.count(last_data[3]) && 
				nums_set.count(last_data[4])) {
				win_money(one_bet);
				won = true;
			}
			else {
				one_bet._index++;
				
			}
		}
		else {
			cerr << "unknow play type" << endl;
			exit(1);
		}

		if (won || one_bet._index >= one_bet._money.size()) {
			display_one_bet(won, one_bet);
		}
		else {
			tmpBets.push_back(one_bet);
		}
	}

	_all_bets.clear();
	_all_bets.insert(_all_bets.end(), tmpBets.begin(), tmpBets.end());
}

