#ifndef _BET_H
#define _BET_H

#include "hot.h"
#include "strategy.h"


class Bet
{
public:
	Bet(Hot &hot);
	~Bet();

	void bet();

private:
	void cal_last_bet();
	void display_one_bet(bool won, const OneBet &one_bet);
	void win_money(const OneBet &one_bet);

	Hot &_hot;
	int _money;
	vector<OneBet> _all_bets;
	Strategy *_stg1;
	Strategy *_stg_ren1;
	Strategy *_stg_ren2;
	Strategy *_stg_ren3;
	Strategy *_stg_ren4;
	Strategy *_stg_ren8;
};



#endif