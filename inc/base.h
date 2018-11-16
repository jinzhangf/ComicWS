#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>


#include <cstdlib>
#include <cstdio>

#ifdef _DEBUG
#define DEBUG_LOG(fmt, args...) \
    do \
    { \
        printf("[debug] "); \
        printf(fmt, ##args); \
        printf("\n"); \
    } while(0)
#else
#define DEBUG_LOG(fmt, args...) \
    do { \
    } while(0)
#endif

using namespace std;

int A(int, int);

int C(int, int);

// 组合
vector<vector<int>> combine2(const vector<int> &vec);

// 标准化
vector<double> normalize(const vector<int> &input);

// 标准化
vector<vector<double> > normalize(const vector<vector<int> > &input);

// 剔除冷数据，n是冷数据个数
vector<int> erase_cold(const vector<int> &data, const vector<double> &cold, int n);