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
	string operand;
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


MancBaby :: MancBaby() {
	this -> store = vector<string>(32, "0");
	this -> instructAddr = 0;
	this -> accumulator = "";
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
		int j = 4;
	(this -> operand).clear();
	(this -> opcode).clear();
	for (int i = 0; i < 5; i++) {
		this -> operand += this -> instruct.at(i);
		j--;
	}
	j = 2;
	for (int i = 0; i < 3; i++) {
		this -> opcode += this -> instruct.at(13+i);
		j--;
	}	
	} catch (...) {
		cout << "Problem with decode() method. " << endl;
	}
	
}

int MancBaby :: execute() {
	try {
	if (this -> opcode == "000") {
		JMP();
	} else if (this -> opcode == "100") {
		JRP();
	} else if (this -> opcode == "010") {
		LDN();
	} else if (this -> opcode == "110") {
		STO();
	} else if (this -> opcode == "001") {
		SUB();
	} else if (this -> opcode == "101") {
		SUB();
	} else if (this -> opcode == "011") {
		CMP();
	} else if (this -> opcode == "111") {
		return -1;
	} else {
		cout << "Error: Invalid opcode" << endl;
		return 1;
	}
	} catch (...) {
		cout<<"Problem with execute() method. " << endl;
	}
	return 0;
	
}

void MancBaby :: JRP() {	
	operand = decToBin(this -> instructAddr + binToDec(this -> store.at(binToDec(this -> operand))));
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
	this -> accumulator = twosCompliment(this -> store.at(binToDec(this -> operand)));
	cout<<"accumulator: " << this->accumulator<<endl;
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
	cout << "original binary (big end): " << binary << endl;
	reverse(binary.begin(), binary.end());
	cout << "little end binary: " << binary << endl;
    int dec = 0;
    int power = 0;
    for (int i = 5; i >= 0; i--, power++) {
        if (binary[i] == '1') {
            dec = pow(2, power) + dec;
        }
    }
    cout << "decimal: " << dec << endl;
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
    	while (binary.length() < 5) {
        	binary = "0" + binary;
    	}
    	return twosCompliment(binary);
	} else {
		while (decimal != 0) {
        	binary = (decimal % 2 == 0 ?"0":"1") + binary;
        	decimal /= 2;
    	}	
    	while (binary.length() < 5) {
        	binary = "0" + binary;
    	}
	}
    
    reverse(binary.begin(), binary.end());
    return binary;
}

string MancBaby :: twosCompliment(string posBinary) {
	int tempDec = binToDec(posBinary);
	string tempBinary = decToBin(tempDec+1);
	string negBinary;
	for (int i = 0; i < static_cast<int>(tempBinary.length()); i++) {
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
	cout<<"Store:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << newMancBaby.store.at(i) << endl;
	}
	cout<< "instruct addr: " << newMancBaby.instructAddr << endl;
	cout<< "instruction: " << newMancBaby.instruct << endl;
	cout<< "opcode: " << newMancBaby.opcode << endl;
	cout<< "operand: " << newMancBaby.operand << endl;


	sleep_for(seconds(2));

	int check = 0;
	while (check < 9){	
		newMancBaby.fetch();
		newMancBaby.decode();
	cout<<"---------------------------------------------" << endl;	
	cout<< "instruct addr: " << newMancBaby.instructAddr << endl;
	cout<< "instruction: " << newMancBaby.instruct << endl;
	cout<< "opcode: " << newMancBaby.opcode << endl;
	cout<<"operand: " << newMancBaby.operand << endl;
	cout<<"accumulator: " << newMancBaby.accumulator << endl;
	
		check = newMancBaby.execute();
		if (check == 1) {
			return 1;
		}
		check++;
			
		for (int i = 0; i < 32; i++) {
		cout << newMancBaby.store.at(i) << endl;
		}
	sleep_for(seconds(10));
	}
	return 0;
}
