/**
  * Project: AC21009 (Computer Systems 2A) Assignment 3 - Small Scale Experimental Machine (SSEM)/'Manchester Baby'
  * Subtitle: Manchester Baby Simulator
  * Name: Paul Ritch, Patrick Turton-Smith (170012743) & Isaac Lowry for Team 16
  * Date: 17/11/2018
  * Program to simulate the working of the SSEM (the Manchester Baby). Loads the program to be run on the simulator from a pre-compiled file and executes it.
**/


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


// Declaration of class, and the variables and methods it contains
class MancBaby {
	
	public:
		vector<string> store; // Machine's store 
		string accumulator;
		int controlInstruct;
		string presentInstruct;
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

};


// Default contructor for objects of type MancBaby
MancBaby :: MancBaby() {
	this -> store = vector<string>(32, "0");
	this -> controlInstruct = 0;
	this -> accumulator = "";
	this -> operand = 0;
	this -> opcode = "";
}


// Method for loading in program to be run from file and placing into store
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


// Method for fetching the next instruction from the store
void MancBaby :: fetch() {
	try {
		this -> controlInstruct = (this -> controlInstruct) + 1;
		presentInstruct = store.at(controlInstruct);
	} catch (...) {
		cout << "Problem with fetch() method." << endl;
	}
}


// Method for decoding the current instruction, parsing it into its opcode and operand
void MancBaby :: decode() {
	try {
		this -> operand = 0;
		(this -> opcode).clear();
		int power = 0;
		for (int i = 0; i < 5; i++, power++) {
			if (this -> presentInstruct.at(i) == '1') {
				this -> operand += pow(2, power);
			}
		}
		for (int i = 0; i < 3; i++) {
			this -> opcode += this -> presentInstruct.at(13+i);
		}	
	} catch (...) {
		cout << "Problem with decode() method. " << endl;
	}	
}


// Method for executing the instruction, calling the method appropriate to the opcode
int MancBaby :: execute() {
	try {
		if (this -> opcode == "000") {
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


// Method for carrying out a JMP instruction (set present instruction counter to operand)
void MancBaby :: JMP() {
	this -> controlInstruct = this -> operand;
}


// Method for carrying out a JRP instruction (add operand to present instruction counter)
void MancBaby :: JRP() {	
	this -> controlInstruct = (this -> controlInstruct + this -> operand);
}


// Method for carrying out an LDN instruction (place the negated operand and place into accumulator)
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


// Method for carrying out an STO instruction (place contents of accumulator into store at required place)
void MancBaby :: STO() {
	this -> store.at(this -> operand) = this -> accumulator;
}


// Method for carrying out a SUB instruction (subtraction of operand from accumulator)
void MancBaby :: SUB() {
	int tempIntAccum = this -> binToDec(this->accumulator);
	int tempIntStore = this -> binToDec(this->store.at(this->operand));
	this -> accumulator = this -> decToBin(tempIntAccum - tempIntStore);
}


// Method for carrying out a CMP instruction (increment present instruction counter if accumulator is negative)
void MancBaby :: CMP() {
	if (binToDec(this -> accumulator) < 0) {
		this -> controlInstruct += 1;
	}
}


// Method to convert a string containing a binary number into an int containing a decimal number. Implements negative numbers using signed bit notation
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


// Method to convert an int containing a decimal number into a string containing a binary number. Implements negative numbers using signed bit notation
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


// Method for displaying the status of all aspects of the machine
void MancBaby :: displayStatus() {
	cout << "__________________________________________________________________________________________________________________________________" << endl << endl;
	cout << "Control Instruction: " << this -> controlInstruct << endl;
	cout << "Present instruction: " << this -> presentInstruct << endl;
	cout << "Opcode from PI: " << this -> opcode;
	if (this -> opcode == "000") {
			cout << " (JRP)";
		} else if (this -> opcode == "100") {
			cout << " (JRP)";
		} else if (this -> opcode == "010") {
			cout << " (LDN)";
		} else if (this -> opcode == "110") {
			cout << " (STO)";
		} else if (this -> opcode == "001") {
			cout << " (SUB)";
		} else if (this -> opcode == "101") {
			cout << " (SUB)";
		} else if (this -> opcode == "011") {
			cout << " (CMP)";
		} else if (this -> opcode == "111") {
			cout << " (STP)";
		} else {
			cout << " (Invalid opcode)";
		}
	cout << "          Operand from PI: " << this -> operand << endl;
	
	cout << "Store:      1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32" << endl;
	for (int r = 0; r < 10; r++) {
		cout << "     " << r;
		for (int c = 0; c < 32; c++) {
			if (this -> store.at(r)[c] == '1') {
				cout << "  \u25AA";
			} else {
				cout << "  \u25AB";
			}
		}
		cout << endl;
	}
	for (int r = 10; r < 32; r++) {
		cout << "    " << r;
		for (int c = 0; c < 32; c++) {
			if (this -> store.at(r)[c] == '1') {
				cout << "  \u25AA";
			} else {
				cout << "  \u25AB";
			}
		}
		cout << endl;
	}
	cout << "				1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32" << endl;
	cout << "Accumulator:	";
	for (int c = 0; c < 32; c++) {
		if (this -> accumulator[c] == '1') {
			cout << "\u25AA ";
		} else {
			cout << "\u25AB ";
		}
	}
}


// Main method for the simulator, creates the variables necessary and calls the other methods to properly simulate the Baby.
int main() {
	MancBaby newMancBaby;
	if (newMancBaby.loadFromFile() == 1) {
		return 1;
	}
	// cout<<"Store:" << endl;
	// for (int i = 0; i < 32; i++) {
	// 	cout << newMancBaby.store.at(i) << endl;
	// }
	// cout<< "instruct addr: " << newMancBaby.controlInstruct << endl;
	// cout<< "instruction: " << newMancBaby.presentInstruct << endl;
	// cout<< "opcode: " << newMancBaby.opcode << endl;
	// cout<< "operand: " << newMancBaby.operand << endl;


	//sleep_for(seconds(2));

	int check = 0;
	while (check != -1){ // Until stop light is lit	
		// cout<<"---------------------------------------------" << endl;	
		// cout<< "instruct addr: " << newMancBaby.controlInstruct << endl;
		newMancBaby.fetch();
		// cout<< "instruction: " << newMancBaby.presentInstruct << endl;
		newMancBaby.decode();
		// cout<<"operand: " << newMancBaby.operand << endl;
		// cout << "opcode: " << newMancBaby.opcode << endl;
		// cout<<"accumulator: " << newMancBaby.accumulator << endl;
		// for (int i = 0; i < 32; i++) {
		// 	cout << newMancBaby.store.at(i) << endl;
		// }
		check = newMancBaby.execute();
		newMancBaby.displayStatus();
	}

	cout << "Stop light lit (STP). Exiting simulator..." << endl;
	return 0;
}
