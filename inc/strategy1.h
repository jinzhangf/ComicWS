#ifndef _STRATEGY1_H_
#define _STRATEGY1_H_


#include "strategy.h"
#include "hot.h"

class Strategy1 : public Strategy
{
public:
	Strategy1(int &money, Hot &hot);
	virtual vector<OneBet> make_decision();

private:
	int &_money;
	Hot &_hot;
};

#endif