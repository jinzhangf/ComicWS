#include "strategy_ren2.h"

Strategy_Ren2::Strategy_Ren2(int &money, Hot &hot) 
	: _money(money), _hot(hot)
{
	//empty
}

Strategy_Ren2::~Strategy_Ren2()
{
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

vector<OneBet> Strategy_Ren2::make_decision()
{
	stats();
	vector<OneBet> ret;
	if (_hot.get_size() < 30) return ret;

	vector<int> last_data = _hot.get_last_data();
	vector<int> hot_data = _hot.get_hot_data({5, 30});
	vector<CmpInfo> hot_sorted_last_data;
	for (auto num : last_data) {
		CmpInfo info;
		info.num = num;
		info.val = hot_data[num - 1];
		hot_sorted_last_data.push_back(info);
	}
	sort(hot_sorted_last_data.begin(), hot_sorted_last_data.end());

	vector<vector<int>> hot_rel = _hot.get_hot_rel_two({5, 30});
	vector<int> 


/*
	cout << "last_data:";
	for (auto val : last_data) {
		cout << val << " ";
	}
	cout << endl;
*/
	for (size_t i = 0; i < last_data.size() - 2; ++i) {
		if (last_data[i] + 1 == last_data[i + 1] &&
			last_data[i + 1] + 1 == last_data[i + 2]) {
			OneBet onebet;
			onebet._play_type = PLAY_THREE;
			onebet._nums.push_back(last_data[i]);
			onebet._nums.push_back(last_data[i + 1]);
			onebet._nums.push_back(last_data[i + 2]);
			set_bet_money(20, 1, 10, 2, 10, 2, onebet);
			ret.push_back(onebet);
			//int m = std::accumulate(onebet._money.begin(), onebet._money.end(), 0);
			//_money -= m;
			//cout << "bet:" << last_data[i] << "," << last_data[i+1] << ","
			//     << last_data[i+2] << " m:" << m << " _money:" << _money << endl;
		}
	}	
	return ret;
}

void Strategy_Ren2::stats()
{
}
