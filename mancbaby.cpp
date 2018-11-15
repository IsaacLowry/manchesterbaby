#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
//#include "mancbaby.h"


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
		string twosCompliment(string);

};



int MancBaby :: loadFromFile() {
	string filePath;
	cout << "Please enter name of file to load program from: ";
	cin >> filePath;
	fstream readFile;

	readFile.open(filePath, ios::in);
	string currLine;
	if (readFile.is_open()) {
		int i = 0;
		while (getline(readFile, currLine) || i < 32) {
			this -> store.at(i) = currLine;
			i++;
		}
		readFile.close();
		return 0;
	} else {
		return 1;
	}

}

void MancBaby :: fetch() {
	this -> instructAddr++;
	instruct = store[instructAddr];
}

void MancBaby :: decode() {
	int j = 4;
	for (int i = 0; i < 5; i++) {
		operand.at(i) = instruct.at(j);
		j--;
	}
	j = 2;
	for (int i = 0; i < 3; i++) {
		opcode.at(i) = instruct.at(12+j);
		j--;
	}
}

int MancBaby :: execute() {
	if (opcode == "000") {
		JMP();
	} else if (opcode == "001") {
		JRP();
	} else if (opcode == "010") {
		LDN();
	} else if (opcode == "011") {
		STO();
	} else if (opcode == "100") {
		SUB();
	} else if (opcode == "101") {
		SUB();
	} else if (opcode == "110") {
		CMP();
	} else if (opcode == "111") {
		return -1;
	} else {
		cout << "Error: Invalid opcode" << endl;
		return 1;
	}
	return 0;
}

void MancBaby :: JRP() {	
	operand = decToBin(this -> instructAddr + binToDec(this -> store[binToDec(this -> operand)]));
	JMP();
}

void MancBaby :: CMP() {
	if (binToDec(this -> accumulator) < 0) { this -> instructAddr+=2;} else { this -> instructAddr++;}
}

void MancBaby :: LDN() {
	this -> accumulator = this -> store[binToDec(this -> operand)];
	twosCompliment(this -> accumulator);
}

void MancBaby :: JMP() {
	this -> instructAddr = binToDec(this -> operand);
}

void MancBaby :: STO() {
	this -> operand = this -> accumulator;
}

void MancBaby :: SUB() {
	this -> accumulator = decToBin(binToDec(this -> accumulator) - binToDec(this -> operand));
}


int MancBaby :: binToDec(string binary) {
	//int base = 1;
    int dec = 0;
    int power = 0;
    for (int i = 7; i >= 0; i--, power++) {
        if (binary[i] == '1') {
            dec = pow(2, power) + dec;
        }
    }
    return dec;
}

string MancBaby :: decToBin(int decimal) {
	string binary;
	if (decimal < 0) {
		decimal = -decimal;
		while (decimal != 0) {
        	binary = (decimal % 2 == 0 ?"0":"1") + binary;
        	decimal /= 2;
    	}	
    	while (binary.length() < 8) {
        	binary = "0" + binary;
    	}
    	return twosCompliment(binary);
	} else {
		while (decimal != 0) {
        	binary = (decimal % 2 == 0 ?"0":"1") + binary;
        	decimal /= 2;
    	}	
    	while (binary.length() < 8) {
        	binary = "0" + binary;
    	}
	}
    
    return binary;
}

string MancBaby :: twosCompliment(string posBinary) {
	int tempDec = binToDec(posBinary);
	string tempBinary = decToBin(tempDec+1);
	string negBinary;
	for (int i = 0; i < tempBinary.length(); i++) {
		if (tempBinary[i] == '0') {
			negBinary[i] = '1';
		} else {
			negBinary[i] = '0';
		}
	}

	return negBinary;
}

int main() {
	MancBaby newMancBaby;
	if (newMancBaby.loadFromFile() == 1) {
		return 1;
	}
	int check = 0;
	while (check == 0){	
		newMancBaby.fetch();
		newMancBaby.decode();
		check = newMancBaby.execute();
		if (check == 1) {
			return 1;
		}
	}
	return 0;
}