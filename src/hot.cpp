#include "hot.h"
#include <string.h>
#include <limits.h>

inline int to_index(int num)
{
	return num - 1;
}

struct DateInfo
{
	int year;
	int month;
	int day;
	int count;
};

DateInfo get_date_info(const string &date)
{
	DateInfo ret;
	ret.year = std::atoi(date.substr(0, 4).c_str());
	ret.month = std::atoi(date.substr(4, 2).c_str());
	ret.day = std::atoi(date.substr(6,2).c_str());
	ret.count = std::atoi(date.substr(8, 2).c_str());
	return ret;
}

bool cmp_date(const string &old_date, const string &new_date)
{
	DateInfo old_date_info = get_date_info(old_date);
	DateInfo new_date_info = get_date_info(new_date);
	if (new_date_info.year > old_date_info.year) {
		return true;
	}
	else if (new_date_info.year < old_date_info.year) {
		return false;
	}

	if (new_date_info.month > old_date_info.month) {
		return true;
	}
	else if (new_date_info.month < old_date_info.month) {
		return false;
	}

	if (new_date_info.day > old_date_info.day) {
		return true;
	}
	else if (new_date_info.day < old_date_info.day) {
		return false;
	}

	return new_date_info.count > old_date_info.count;
}

Hot::Hot() : _types({5, 10, 30, 50, 100})
{
	// init
	for (auto type : _types) {
		_hot_data[type];
		_hot_rel[type];
	}
}

void Hot::set_history(const string &pre_file)
{
	// read data
	map<int, vector<int>> table; // key is used for sorting
	ifstream infile(pre_file.c_str());
	if (!infile) {
		cerr << "cannot open file " << pre_file << endl;
		exit(1);
	}

	string line;
	int line_nr = 0;
	string last_date = "0000000000";
	while (getline(infile, line)) {
		line_nr++;
		istringstream is(line);
		string date;
		vector<int> nums(5);
		char comma;
		is >> date >> nums[0] >> comma >> nums[1] >> comma >> nums[2] 
		   >> comma >> nums[3] >> comma >> nums[4];
		//cout << date << "\t" << nums[0] << "," << nums[1] << ","
		//     << nums[2] << "," << nums[3] << "," << nums[4] << endl;
		if (!cmp_date(last_date, date)) {
			cerr << "Error date. old:" << last_date << ", new:" << date << endl;
			exit(1);
		}
		last_date = date;
		table[INT_MAX - line_nr] = nums;
	}
	infile.close();

	for (auto &item : table) {
		read_data(item.second);
	}
}

int Hot::get_hot_data(int type, int num)
{
	return _hot_data[type]._hd[to_index(num)];
}

vector<int> Hot::get_hot_data(int type)
{
	vector<int> ret(11);
	for (int i = 0; i < 11; ++i) {
		ret[i] = _hot_data[type]._hd[i];
	}
	return ret;
}

vector<int> Hot::get_hot_data(vector<int> types)
{
	vector<int> ret(11, 0);
	for (auto type : types) {
		auto tmp = get_hot_data(type);
		for (size_t i = 0; i < ret.size(); ++i) {
			ret[i] += tmp[i];
		}
	}
	return ret;
}

vector<double> Hot::get_hot_data_stats()
{
	vector<double> ret(11, 0);
	for (auto type : _types) {
		vector<int> hot_data = get_hot_data(type);
		vector<double> nml = normalize(hot_data);
		for (size_t i = 0; i < nml.size(); ++i) {
			ret[i] += nml[i];
		}
	}
	for (size_t i = 0; i < ret.size(); ++i) {
		ret[i] /= _types.size();
	}
	return ret;
}

void Hot::inc_hot_data(int type, int num)
{
	_hot_data[type]._hd[to_index(num)]++;
}

int Hot::get_hot_rel_two(int type, int num1, int num2)
{
	return _hot_rel[type]._hr[to_index(num1)][to_index(num2)];
}

vector<vector<int>> Hot::get_hot_rel_two(int type)
{
	vector<vector<int>> ret;
	for (int i = 0; i < 11; ++i) {
		vector<int> vec;
		for (int j = 0; j < 11; ++j) {
			int val = _hot_rel[type]._hr[i][j];
			vec.push_back(val);
		}
		ret.push_back(vec);
	}
	return ret;
}

vector<vector<int>> Hot::get_hot_rel_two(vector<int> types)
{
	vector<vector<int>> ret(11, vector<int> (11, 0));
	for (auto type : types) {
		auto tmp = get_hot_rel_two(type);
		for (size_t i = 0; i < 11; ++i) {
			for (size_t j = 0; j < 11; ++j) {
				ret[i][j] += tmp[i][j];
			}
		}
	}
	return ret;
}


vector<vector<double>> Hot::get_hot_rel_two_stats()
{
	vector<vector<double>> ret(11, vector<double> (11, 0));
	for (auto type : _types) {
		vector<vector<int>> hot_rel = get_hot_rel_two(type);
		vector<vector<double>> nml = normalize(hot_rel);
		for (size_t i = 0; i < nml.size(); ++i) {
			for (size_t j = 0; j < nml.size(); ++j) {
				ret[i][j] += nml[i][j];
			}
		}
	}
	for (size_t i = 0; i < ret.size(); ++i) {
		for (size_t j = 0; j < ret.size(); ++j) {
			ret[i][j] /= _types.size();
		}
	}
	return ret;
}

void Hot::inc_hot_rel(int type, int num1, int num2)
{
	if (num1 == num2)
		return;

	_hot_rel[type]._hr[to_index(num1)][to_index(num2)]++;
}

void Hot::reset_hot(int type)
{
	memset(&(_hot_data[type]._hd), 0, sizeof(HotData));
	memset(&(_hot_rel[type]._hr), 0, sizeof(HotRel));	
}

void Hot::update_hot()
{
	if (_types.size() != _hot_data.size() || 
		_types.size() != _hot_rel.size()) {
		cerr << "update_hot failed." << endl;
		return ;
	}

	for (auto type : _types) {
		reset_hot(type);
		int end_index = _data.size() > type ? _data.size() - type : 0;
		for (int i = _data.size() - 1; i >= end_index; --i) {
			for (auto num1 : _data[i]) {
				inc_hot_data(type, num1);
				for (auto num2 : _data[i]) {
					inc_hot_rel(type, num1, num2);
				}
			}
		}
	}
}

bool check_data(int item)
{
	return item >= 1 && item <= 11;
}

int Hot::read_data(const vector<int> &in_data)
{
	if (in_data.size() != 5) {
		cerr << "in_data size != 5" << endl;
		return -1;
	}

	if (!check_data(in_data[0]) ||
		!check_data(in_data[1]) ||
		!check_data(in_data[2]) ||
		!check_data(in_data[3]) ||
		!check_data(in_data[4])) {
		cerr << "in_data check_data false." << endl;
		return -2;
	}

	_data.push_back(in_data);
	/*
	for (auto val : in_data) {
		cout << val << "\t";
	}
	cout << endl;
	*/
	update_hot();

	return 0;
}

inline char to_char(int num)
{
	if (num >= 1 && num <= 9)
		return (char)('1' + (num - 1));

	if (num == 10)
		return 'A';

	if (num == 11)
		return 'B';

	return 'A';
}

void Hot::display_hot_origin()
{
	for (auto type : _types) {
		cout << "type: " << type << endl;
		for (int num = 1; num <= 11; ++num) {
			cout << to_char(num) << "(" << get_hot_data(type, num) << ") ";
		}
		cout << endl;
	}


	// cout << "hot rel: " << endl;
	// for (int num1 = 1; num1 <= 11; ++num1) {
	// 	cout << to_char(num1) << ":\t";
	// 	for (int num2 = 1; num2 <= 11; ++num2) {
	// 		cout << to_char(num1) << "," << to_char(num2) << "(" 
	// 		     << get_hot_rel_two(type, num1, num2) << ")\t";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
}

void Hot::display_hot_stats()
{
	vector<double> ret(11, 0);
	for (auto type : _types) {
		vector<int> hot_data = get_hot_data(type);
		vector<double> nml = normalize(hot_data);
		cout << "type:" << type << " - ";
		for (size_t i  = 0; i < nml.size(); ++i) {
			cout << nml[i] << " ";
		}
		cout << endl;
		for (size_t i = 0; i < nml.size(); ++i) {
			ret[i] += nml[i];
		}
	}
	cout << "all : " << " - ";
	for (size_t i = 0; i < ret.size(); ++i) {
		ret[i] /= _types.size();
		cout << ret[i] << " ";
	}
	cout << endl;
}
void Hot::display_data(int n)
{
	int i = _data.size() > n ? _data.size() - n : 0;
	cout << "_data: " << endl;
	for (; i < _data.size(); ++i) {
		for (int j = 0; j < 5; ++j) {
			cout << to_char(_data[i][j]) << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

vector<int> Hot::get_last_data()
{
	return _data.back();
}

vector<int> Hot::get_types()
{
	return _types;
}















