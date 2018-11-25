#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "base.h"

enum PlayType
{
	PLAY_ONE = 1,     // 前一
	PLAY_TWO = 2,     // 任选二
	PLAY_THREE = 3,   //任选三
	PLAY_EIGHT = 8,  // 任选八

	PLAY_ONE_DOUBLE = 11, 
	PLAY_ONE_ANY = 12, // 任一
};

struct OneBet
{
	int _play_type;
	double _price;
	vector<int> _nums;
	double _hot_score;
	double _rel_score;
	vector<int> _money;
	size_t _index; //inde小于_money.size();
};


class Strategy
{
public:
	virtual ~Strategy() {}
	virtual vector<OneBet> make_decision() = 0;
	virtual void win_or_not(bool win) {}

protected:
	void set_bet_money(int count, int times, OneBet &one_bet);
	void set_bet_money(int count, int init_times, double earn_rate, OneBet &one_bet);
	void set_bet_money(int count, int init_times, 
		               int front_n, double front_earn_rate,
		               int back_n, double back_earn_rate, 
		               OneBet &one_bet);
	void set_bet_money2(int count, int less_won_money, OneBet &one_bet);

private:
	void set_price(OneBet &one_bet);
};

#endif