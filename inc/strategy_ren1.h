#ifndef _STRATEGY_REN1_H_
#define _STRATEGY_REN1_H_


#include "strategy.h"
#include "hot.h"


class Strategy_Ren1 : public Strategy
{
public:
	Strategy_Ren1(int &money, Hot &hot);
	virtual ~Strategy_Ren1();
	virtual vector<OneBet> make_decision();

private:
	void stats();
	int max_miss(size_t &index);
	int sec_max_miss(size_t &index, int max_miss_index);

	int &_money;
	Hot &_hot;
	vector<int> _miss;
	map<int, int> _miss_stats; //第一遗漏的统计
	map<int, map<int, int>> _sec_miss_stats;
};

#endif