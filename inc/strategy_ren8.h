#ifndef _STRATEGY_REN8_H_
#define _STRATEGY_REN8_H_


#include "strategy.h"
#include "hot.h"


class Strategy_Ren8 : public Strategy
{
public:
	Strategy_Ren8(int &money, Hot &hot);
	virtual ~Strategy_Ren8();
	virtual vector<OneBet> make_decision();
	virtual void win_or_not(bool state);

private:
	void stats();

	int &_money;
	Hot &_hot;
	bool _last_state;
	int _state_cnt;
	map<int, int> _win_table;
	map<int, int> _lose_table;
};

#endif
