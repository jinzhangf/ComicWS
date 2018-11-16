#include "base.h"
#include "hot.h"
#include "bet.h"

void print_help()
{
	cout << "***************** help doc *****************" << endl;
	cout << " a) read data (with 5 nums)" << endl;
	cout << " b) display data (with n)" << endl;
	cout << " c) display hot statiscs (origin)" << endl;
	cout << " d) display hot statiscs (normalized)" << endl;
	cout << "********************************************" << endl << endl;
}

void read_data(Hot &hot)
{
	vector<int> nums(5);
	cin >> nums[0] >> nums[1] >> nums[2] >> nums[3] >> nums[4];
	if (!cin) {
		cerr << "read_data wrong." << endl;
		exit(1);
	}

	hot.read_data(nums);
}

void display_data(Hot &hot)
{
	int n;
	cin >> n;
	if (!cin) {
		cerr << "display_data wrong." << endl;
		exit(1);
	}

	hot.display_data(n);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
        cerr << "argc should be 2" << endl;
        return -1;
	}
	
	Hot hot(argv[1]);
	Bet bet(hot);
	print_help();
	input();
	char cmd;
	while (cin >> cmd) {
		switch(cmd) {
			case 'a':
				read_data(hot);
				bet.bet();
				break;
			case 'b':
				display_data(hot);
				break;
			case 'c':
				hot.display_hot_origin();
				break;
			case 'd':
				hot.display_hot_stats();
				break;
			default:
				print_help();
				break;
		}
		input();
	}

	if (!cin) {
		cerr << "wrong cmd." << endl;
		exit(1);
	}
	
	return 0;
}

