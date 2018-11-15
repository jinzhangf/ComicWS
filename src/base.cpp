#include "base.h"
#include <limits.h>

int A(int n, int m)
{
	int ret = 1;
	for (int i = n - m + 1; i <= n; ++i) {
		ret *= i;
	}
	return ret;
}

int C(int n, int m)
{
	return A(n, m) / A(m, m);
}

inline int min(int a, int b)
{
	return a < b ? a : b;
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}

vector<double> normalize(const vector<int> &input)
{
	int min_val = INT_MAX;
	int max_val = INT_MIN;
	for (auto val : input) {
		min_val = min(val, min_val);
		max_val = max(val, max_val);
	}

	vector<double> output(input.size());
	for (size_t i = 0; i < input.size(); ++i) {
		output[i] = (double)(input[i] - min_val) / (double)(max_val - min_val);
	}
	return output;
}

vector<vector<double> > normalize(const vector<vector<int> > &input)
{
	int min_val = INT_MAX;
	int max_val = INT_MIN;
	for (size_t i = 0; i < input.size(); ++i) {
		for (size_t j = 0; j < input[0].size(); ++j) {
			min_val = min(input[i][j], min_val);
			max_val = max(input[i][j], max_val);
		}
	}

	vector<vector<double> > output;
	for (size_t i = 0; i < input.size(); ++i) {
		vector<double> vec;
		for (size_t j = 0; j < input[0].size(); ++j) {
			double val = (double)(input[i][j] - min_val) / (double)(max_val - min_val);
			vec.push_back(val);
		}
		output.push_back(vec);
	}
	return output;
}


