#include "base.h"

#ifndef _HOT_H_
#define _HOT_H_

struct HotData
{
	int _hd[11];
};

struct HotRel
{
	int _hr[11][11];
};

class Hot
{
public:
	Hot(const string &pre_file);

	int read_data(const vector<int> &in_data);

	vector<int> get_last_data();
	vector<int> get_types();

	int get_hot_data(int type, int num);
	vector<int> get_hot_data(int type);
	vector<double> get_hot_data_stats();

	int get_hot_rel_two(int type, int num1, int num2);
	vector<vector<int>> get_hot_rel_two(int type);
	vector<vector<double>> get_hot_rel_two_stats();

	void display_hot(int type);
	void display_data(int n);

private:
	void update_hot();
	void reset_hot(int type);
	void inc_hot_data(int type, int num);
	void inc_hot_rel(int type, int num1, int num2);
	
	vector<int> _types;
	vector<vector<int>> _data;
	map<int, HotData> _hot_data;
	map<int, HotRel> _hot_rel;
};


#endif