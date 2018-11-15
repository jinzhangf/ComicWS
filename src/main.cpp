#include "base.h"
#include "hot.h"
#include "bet.h"

void print_help()
{
	cout << "***************** help doc *****************" << endl;
	cout << " 1) read data" << endl;
	cout << " 2) display data" << endl;
	cout << " 3) display hot statiscs" << endl;
	cout << "********************************************" << endl << endl;
}

void read_data(Hot &hot)
{
	vector<int> nums(5);
	cin >> nums[0] >> nums[1] >> nums[2] >> nums[3] >> nums[4];
	if (!cin) {
		cerr << "read_data wrong." << endl;
		cin.clear();
		cin.sync();
		return;
	}

	hot.read_data(nums);
	cout << "read_data success!" << endl << endl;
}

void display_data(Hot &hot)
{
	int n;
	cin >> n;
	if (!cin) {
		cerr << "display_data wrong." << endl;
		cin.clear();
		cin.sync();
		return;
	}

	hot.display_data(n);
}

void display_hot(Hot &hot)
{
	int type;
	cin >> type;
	if (!cin) {
		cerr << "display_hot wrong." << endl;
		cin.clear();
		cin.sync();
		return;
	}

	hot.display_hot(type);
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
	int cmd;
	while (cin >> cmd) {
		switch(cmd) {
			case 1:
				read_data(hot);
				bet.bet();
				break;
			case 2:
				display_data(hot);
				break;
			case 3:
				display_hot(hot);
			default:
				print_help();
				break;
		}
	}
	//hot.display(100);
	//hot.display(5);

	
	return 0;
}

