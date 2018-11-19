#include "strategy_ren3.h"

Strategy_Ren3::Strategy_Ren3(int &money, Hot &hot) 
	: _money(money), _hot(hot)
{
	//empty
}

Strategy_Ren3::~Strategy_Ren3()
{
}

vector<OneBet> Strategy_Ren3::make_decision()
{
	stats();

	vector<OneBet> ret;
	vector<int> last_data = _hot.get_last_data();
	sort(last_data.begin(), last_data.end());
	for (size_t i = 0; i < last_data.size() - 2; ++i) {
		if (last_data[i] + 1 == last_data[i + 1] &&
			last_data[i + 1] == last_data[i + 2]) {
			OneBet onebet;
			onebet._play_type = PLAY_THREE;
			onebet._nums.push_back(last_data[i]);
			onebet._nums.push_back(last_data[i + 1]);
			onebet._nums.push_back(last_data[i + 2]);
			set_bet_money(20, 1, 0.3, onebet);
			ret.push_back(onebet);
			_money -= std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
		}
	}	
	return ret;
}

void Strategy_Ren3::stats()
{
}
