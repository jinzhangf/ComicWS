#ifndef _STRATEGY_REN4_H_
#define _STRATEGY_REN4_H_


#include "strategy.h"
#include "hot.h"


class Strategy_Ren4 : public Strategy
{
public:
	Strategy_Ren4(int &money, Hot &hot);
	virtual ~Strategy_Ren4();
	virtual vector<OneBet> make_decision();

private:
	void stats();

	int &_money;
	Hot &_hot;
	set<int> _last_data_set;
	map<int, int> _table; // key: 隔的期数， value：次数
	int _count; //不出现4个重号的期数
};

#endif