#include "strategy1.h"

Strategy1::Strategy1(int &money, Hot &hot) : _money(money), _hot(hot)
{
	//empty
	cout << "Strategy1 !" << endl;
}

Strategy1::~Strategy1()
{
	cout << "Strategy1 ~" << endl;
}

vector<OneBet> Strategy1::make_decision()
{
	vector<OneBet> ret;
	vector<int> last_data = _hot.get_last_data();
	vector<double> hot_stats = _hot.get_hot_data_stats();
	last_data = erase_cold(last_data, hot_stats, 2);
	vector<vector<int>> choices = combine2(last_data);
	vector<vector<double>> rel_stats = _hot.get_hot_rel_two_stats();

	for (auto &item : choices) {
		int a = item[0];
		int b = item[1];
		OneBet onebet;
		onebet._play_type = PLAY_TWO;
		onebet._nums.push_back(a);
		onebet._nums.push_back(b);
		set_bet_money(5, 10, 0.3, onebet);
		onebet._hot_score = hot_stats[a-1] + hot_stats[b-1];
		onebet._rel_score = rel_stats[a-1][b-1] + rel_stats[b-1][a-1];
		if (onebet._hot_score > 1.7 && onebet._rel_score > 1.7) {
			ret.push_back(onebet);
			_money -= std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
		}
	}

	return ret;
}