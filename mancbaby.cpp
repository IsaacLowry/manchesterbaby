#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <bits/stdc++.h>

#include<chrono>
#include<thread>

using namespace std;

using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;

class MancBaby {
	

	public:
		vector<string> store;
	string accumulator;
	int instructAddr;
	string instruct;
	string opcode;
	int operand;
		MancBaby();
		int loadFromFile();
		void fetch();
		void decode();
		int execute();
		void displayStatus();
		void JRP();
		void JMP();
		void LDN();
		void STO();
		void SUB();
		void CMP();
		string decToBin(int);
		int binToDec(string);
		//string twosCompliment(string);

};


MancBaby :: MancBaby() {
	this -> store = vector<string>(32, "0");
	this -> instructAddr = 0;
	this -> accumulator = "";
	this -> operand = 0;
	this -> opcode = "";
}


int MancBaby :: loadFromFile() {
	try {
		string filePath;
		cout << "Please enter name of file to load program from: ";
		cin >> filePath;
		fstream readFile;

		readFile.open(filePath, ios::in);
		string currLine;
		if (readFile.is_open()) {
			int i = 0;
			while (getline(readFile, currLine) && i < 32) {
				this -> store.at(i) = currLine;
				i++;
			}
			readFile.close();
			return 0;
		} else {
			cout << "Error reading file. Check file exists." << endl;
			return 1;
		}	
	} catch(...) {
		cout << "Error reading file" << endl;
		return 1;
	}
}


void MancBaby :: fetch() {
	try {
		this -> instructAddr = (this -> instructAddr) + 1;;
		instruct = store.at(instructAddr);
	} catch (...) {
		cout << "Problem with fetch() method." << endl;
	}
}


void MancBaby :: decode() {
	try {
		this -> operand = 0;
		(this -> opcode).clear();
		int power = 0;
		for (int i = 0; i < 5; i++, power++) {
			if (this -> instruct.at(i) == '1') {
				this -> operand += pow(2, power);
			}
		}
		for (int i = 0; i < 3; i++) {
			this -> opcode += this -> instruct.at(13+i);
		}	
	} catch (...) {
		cout << "Problem with decode() method. " << endl;
	}	
}

int MancBaby :: execute() {
	try {
		if (this -> opcode == "000") {
			cout << opcode << " - JMP" << endl;
			JMP();
		} else if (this -> opcode == "100") {
			cout << opcode << " - JRP" << endl;
			JRP();
		} else if (this -> opcode == "010") {
			cout << opcode << " - LDN" << endl;
			LDN();
		} else if (this -> opcode == "110") {
			cout << opcode << " - STO" << endl;
			STO();
		} else if (this -> opcode == "001") {
			cout << opcode << " - SUB" << endl;
			SUB();
		} else if (this -> opcode == "101") {
			cout << opcode << " - SUB" << endl;
			SUB();
		} else if (this -> opcode == "011") {
			cout << opcode << " - CMP" << endl;
			CMP();
		} else if (this -> opcode == "111") {
			cout << opcode << " - STP" << endl;
			return -1;
		} else {
			cout << "Error: Invalid opcode" << endl;
			return 1;
		}
	} catch (...) {
		cout<<"Problem with execute() method. " << endl;
		return 1;
	}
	return 0;
}


void MancBaby :: JRP() {	
	this -> operand = (this -> instructAddr + binToDec(this -> store.at(this -> operand)));
	JMP();
}


void MancBaby :: CMP() {
	if (binToDec(this -> accumulator) < 0) {
		this -> instructAddr += 2;
	} else { 
		this -> instructAddr += 1;
	}
}


void MancBaby :: LDN() {
	string temp = this -> store.at(this -> operand);
	if (temp.at(31) == '0') {
		temp.at(31) = '1';
	} else {
		temp.at(31) = '0';
	}
	this -> accumulator = temp;
	cout<<"accumulator: " << this->accumulator<<endl;
}


void MancBaby :: JMP() {
	this -> instructAddr = this -> operand;
}


void MancBaby :: STO() {
	this -> store.at(this -> operand) = this -> accumulator;
}


void MancBaby :: SUB() {
	int tempIntAccum = this->binToDec(this->accumulator);
	int tempIntStore = this->binToDec(this->store.at(this->operand));
	cout << "SUB result to store: " << (tempIntAccum - tempIntStore);
	this -> accumulator = this->decToBin(tempIntAccum - tempIntStore);
}


int MancBaby :: binToDec(string binary) {
    int dec = 0;
    int power = 0;
    for (int i = 0; i < 31; i++) {
    	if (binary[i] == '1') {
    		dec += pow(2, power);
    	}
        power++;
    }
    if (binary[31] == '1') {
    	dec = -dec;
    }
    return dec;
}

string MancBaby :: decToBin(int origDecimal) {
	int tempDecimal;
	string binary;
	if (origDecimal < 0) {
		tempDecimal = -origDecimal;
	} else {
		tempDecimal = origDecimal;
	}
	while (tempDecimal != 0) {
       	binary = binary + (tempDecimal % 2 == 0 ?"0":"1");
       	tempDecimal /= 2;
    }	
    while (binary.length() < 31) {
       	binary = binary + "0";
    }
	if (origDecimal < 0) {
		binary = binary + '1';
	} else {
		binary = binary + '0';
	}
    return binary;
}


int main() {
	MancBaby newMancBaby;
	if (newMancBaby.loadFromFile() == 1) {
		return 1;
	}
	cout<<"Store:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << newMancBaby.store.at(i) << endl;
	}
	cout<< "instruct addr: " << newMancBaby.instructAddr << endl;
	cout<< "instruction: " << newMancBaby.instruct << endl;
	cout<< "opcode: " << newMancBaby.opcode << endl;
	cout<< "operand: " << newMancBaby.operand << endl;


	//sleep_for(seconds(2));

	int check = 0;
	while (check < 9){	
		cout<<"---------------------------------------------" << endl;	
		cout<< "instruct addr: " << newMancBaby.instructAddr << endl;
		newMancBaby.fetch();
		cout<< "instruction: " << newMancBaby.instruct << endl;
		newMancBaby.decode();
		cout<<"operand: " << newMancBaby.operand << endl;
		cout << "opcode: " << newMancBaby.opcode << endl;
		cout<<"accumulator: " << newMancBaby.accumulator << endl;
		for (int i = 0; i < 32; i++) {
			cout << newMancBaby.store.at(i) << endl;
		}
		check = newMancBaby.execute();
		if (check == -1) {
			return 1;
		}
		check++;
			
		
	//sleep_for(seconds(10));
	}
	return 0;
}
