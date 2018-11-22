#ifndef _STRATEGY_REN2_H_
#define _STRATEGY_REN2_H_


#include "strategy.h"
#include "hot.h"


class Strategy_Ren2 : public Strategy
{
public:
	Strategy_Ren2(int &money, Hot &hot);
	virtual ~Strategy_Ren2();
	virtual vector<OneBet> make_decision();

private:
	void stats();

	int &_money;
	Hot &_hot;
};

#endif
