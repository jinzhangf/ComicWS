#ifndef _STRATEGY_REN3_H_
#define _STRATEGY_REN3_H_


#include "strategy.h"
#include "hot.h"


class Strategy_Ren3 : public Strategy
{
public:
	Strategy_Ren3(int &money, Hot &hot);
	virtual ~Strategy_Ren3();
	virtual vector<OneBet> make_decision();

private:
	void stats();

	int &_money;
	Hot &_hot;
};

#endif
