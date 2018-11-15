#include "bet.h"
#include "strategy1.h"

Bet::Bet(Hot &hot) : _hot(hot)
{
	// empty
}

void Bet::bet()
{
	cal_last_bet();
	Strategy *stg1 = new Strategy1(_money / 10, _hot);
	vector<OneBet> bets = stg1->make_decision();
	_all_bets.insert(_all_bets.end(), bets.begin(), bets.end());
}

inline bool check_one_bet(const OneBet & one_bet)
{
	if ((size_t)one_bet._play_type != one_bet._nums.size()) {
		cerr << "PlayType:" << one_bet._play_type 
		     << ", nums.size=" << one_bet._nums.size() << endl;
		return false;
	}
	return true;
}

void display_one_bet(bool won, const OneBet & one_bet)
{
	cout << won << " " << one_bet._play_type << " ";
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

