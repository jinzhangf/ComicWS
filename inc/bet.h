#ifndef _BET_H
#define _BET_H

#include "hot.h"
#include "strategy.h"



class Bet
{
public:
	Bet(Hot &hot);

	void bet();

private:
	void cal_last_bet();

	Hot &_hot;
	int _money;
	vector<OneBet> _all_bets;
};



#endif