#include <vector>
#include <iostream>
#include <fstream>
#include "mancbaby.h"


void MancBaby :: jmp() {
	this -> instructAddr = binToDec(this -> operand);
}

void MancBaby :: sto() {
	this -> operand = this -> accumulator;
}

void MancBaby :: sub() {
	this -> accumulator = decToBin(binToDec(this -> accumulator)) - (binToDec(this -> operand));
}


int binToDec(string binary) {
	//int base = 1;
    int dec = 0;
    int power = 0;
    for (int i = 7; i >= 0; i--, power++) {
        if (binary[i] == "1") {
            dec = pow(2, power) + dec;
        }
    }
    return dec;
}

string decToBin(int decimal) {
	string binary;
	if (decimal > 0) {
		while (decimal != 0) {
        	binary = (decimal % 2 == 0 ?"0":"1") + binary;
        	decimal /= 2;
    	}	
    	while (binary.length() < 8) {
        	binary = "0" + binary;
    	}
	} else {
		binary = twosCompliment(decimal);
	}
    
    return binary;
}

string twosCompliment(string posBinary) {
	int tempDec = binToDec(posBinary);
	string tempBinary = decToBin(tempDec+1);
	string negBinary;
	for (int i = 0; i < tempBinary.length(); i++) {
		if (tempBinary[i] == "0") {
			negBinary[i] = "1";
		} else {
			negBinary[i] = "0";
		}
	}

	return negBinary;
}
