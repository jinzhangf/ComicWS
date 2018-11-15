#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "base.h"

enum PlayType
{
	PLAY_ONE = 1,     // 前一
	PLAY_TWO = 2,     // 任选二
	PLAY_THREE = 3,   //任选三
};

struct OneBet
{
	PlayType _play_type;
	vector<int> _nums;
	double _hot_score;
	double _rel_score;
	int _money;
};

class Strategy
{
public:
	virtual vector<OneBet> make_decision() = 0;
};

#endif