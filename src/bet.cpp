#include "bet.h"
#include "strategy1.h"

Bet::Bet(Hot &hot) : _hot(hot)
{
	// empty
	_money = INIT_MONEY;
}

void Bet::bet()
{
	cal_last_bet();
	Strategy *stg1 = new Strategy1(_money, _hot);
	vector<OneBet> bets = stg1->make_decision();
	_all_bets.insert(_all_bets.end(), bets.begin(), bets.end());
}

inline bool check_one_bet(const OneBet & one_bet)
{
	if ((size_t)one_bet._play_type != one_bet._nums.size()) {
		cerr << "Error: PlayType:" << one_bet._play_type 
		     << ", nums.size=" << one_bet._nums.size() << endl;
		exit(1);
	}
	return true;
}

void Bet::display_one_bet(bool won, const OneBet &one_bet)
{
	cout << "won:" << won << " ";
	cout << "type:"<< one_bet._play_type << " ";
	cout << "nums:";
	for (auto num : one_bet._nums) {
		cout << num;
		if (num != one_bet._nums.back()) {
			cout << ",";
		}
	}
	cout << " ";
	cout << "hot_score:" << one_bet._hot_score << " ";
	cout << "rel_score:" << one_bet._rel_score << " ";
	cout << "m:" << _money;
	cout << endl;
}

void Bet::cal_last_bet()
{
	vector<int> last_data = _hot.get_last_data();
	set<int> last_data_set(last_data.begin(), last_data.end());

	for (auto &one_bet : _all_bets) {
		if (!check_one_bet(one_bet)) continue;
		bool won = false;

		if (one_bet._play_type == PLAY_ONE) {
			if (one_bet._nums.front() == last_data.front()) {
				_money += one_bet._money / 2 * 13;
				won = true; 
			}
		}
		else if (one_bet._play_type == PLAY_TWO) {
			if (last_data_set.count(one_bet._nums[0]) && 
				last_data_set.count(one_bet._nums[1])) {
				_money += one_bet._money / 2 * 6;
				won = true;
			}
		}
		else if (one_bet._play_type == PLAY_THREE) {
			if (last_data_set.count(one_bet._nums[0]) && 
				last_data_set.count(one_bet._nums[1]) && 
				last_data_set.count(one_bet._nums[2])) {
				_money += one_bet._money / 2 * 19;
				won = true;
			}
		}

		display_one_bet(won, one_bet);
	}

	_all_bets.clear();
}

