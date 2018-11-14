#include <vector>
#include <iostream>

using namespace std;


class MancBaby {
	vector<string> store;
	string accumulator;
	int instructAddr;
	string instruct;
	string opcode;
	string operand;

	public:
		MancBaby();
		int loadFromFile();
		string fetch();
		void decode(string);
		int execute();
		void displayStatus();

}

