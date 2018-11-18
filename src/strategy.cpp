#include "strategy.h"


void Strategy::set_price(OneBet &one_bet)
{
	if (one_bet._play_type == PLAY_ONE) {
		one_bet._price = 6.5;
	}
	else if (one_bet._play_type == PLAY_TWO) {
		one_bet._price = 3.0;
	}
	else if (one_bet._play_type == PLAY_THREE) {
		one_bet._price = 9.5;
	}
	else if (one_bet._play_type == PLAY_ONE_DOUBLE) {
		one_bet._price = 3.25;
	}
	else {
		cerr << "unknow play_type:" << one_bet._play_type << endl;
		exit(1);
	}
}

inline void check_money(int &m)
{
	if (m % 2) {
		m++;
	}
}

void display_money(const OneBet &one_bet)
{
	int sum = 0;
	for (auto val : one_bet._money) {
		cout << val << " ";
		sum += val;
	}
	cout << " all:" << sum << endl;
}

void Strategy::set_bet_money(int count, int times, OneBet &one_bet)
{
	set_price(one_bet);
	one_bet._index = 0;
	one_bet._money = vector<int> (count, times * 2);
	//display_money(one_bet);
}

void Strategy::set_bet_money(int count, int init_times, double earn_rate, OneBet &one_bet)
{
	set_price(one_bet);
	one_bet._index = 0;
	one_bet._money.clear();
	int all = init_times * 2;
	if (one_bet._play_type > 10) {
		all *= 2;
	}
	one_bet._money.push_back(all);

	if (one_bet._price - 1 - earn_rate < 0) {
		cerr << "invalid earn_rate:" << earn_rate << endl;
		exit(1);
	}

	for (int i = 1; i < count; ++i) {
		int m = (1+earn_rate) * all / (one_bet._price - 1 - earn_rate) + 0.5;
		check_money(m);
		one_bet._money.push_back(m);
		all += m;
	}
	display_money(one_bet);
}

void Strategy::set_bet_money(int count, int init_times, 
	               int front_n, double front_earn_rate,
	               int back_n, double back_earn_rate, 
	               OneBet &one_bet)
{
	set_price(one_bet);
	one_bet._index = 0;
	one_bet._money.clear();
	int all = init_times * 2;
	if (one_bet._play_type > 10) {
		all *= 2;
	}
	one_bet._money.push_back(all);

	if (front_n + back_n != count) {
		cerr << "front_n + back_n != count" << endl;
		exit(1);
	}

	if (one_bet._price - 1 - front_earn_rate < 0) {
		cerr << "invalid front_earn_rate:" << front_earn_rate << endl;
		exit(1);
	}

	if (one_bet._price - 1 - back_earn_rate < 0) {
		cerr << "invalid back_earn_rate:" << back_earn_rate << endl;
		exit(1);
	}

	for (int i = 1; i < front_n; ++i) {
		int m = (1+front_earn_rate) * all / (one_bet._price - 1 - front_earn_rate) + 0.5;
		check_money(m);
		one_bet._money.push_back(m);
		all += m;
	}

	for (int i = front_n; i < count; ++i) {
		int m = (1+back_earn_rate) * all / (one_bet._price - 1 - back_earn_rate) + 0.5;
		check_money(m);
		one_bet._money.push_back(m);
		all += m;
	}
	//display_money(one_bet);
}



void Strategy::set_bet_money2(int count, int less_won_money, OneBet &one_bet)
{
	set_price(one_bet);
	one_bet._index = 0;
	one_bet._money.clear();
	int all = 0;
	
	for (int i = 0; i < count; ++i) {
		int m = (less_won_money + all) / (one_bet._price - 1) + 0.5;
		check_money(m);
		one_bet._money.push_back(m);
		all += m;
	}
	//display_money(one_bet);
}






