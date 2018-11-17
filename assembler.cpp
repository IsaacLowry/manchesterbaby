#include <iostream>
#include <string>
#include <cctype>
#include <utility>
using namespace std;
//global variable final output
string out = "00000000000000000000000000000000";

string bigendbinary(int i) {
	string num = "";
	while (i != 0) {

		num += to_string(i % 2);
		//cout<< num<< endl;
		i = i / 2;

	}
	return num;

}



string getpadding(string function, string operand) {

	int lenfun = function.length();
	int oplength = operand.length();
	int ans = 32 - 8 - oplength - lenfun;
	string padding = "";
	for (int k = 0; k < ans; k++) {
		padding += "0";
	}
	return padding;
}




string getinstruction(string word, string instruset[7][2]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 1; j++) {
			if (instruset[i][j] == word) {

				//cout  << instruset[i][j+1];
				return instruset[i][j + 1];
			}

		}
	}
}

bool instructionlookup(string word, string instruset[7][2]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 1; j++) {
			if (instruset[i][j] == word) {

				//cout  << instruset[i][j+1] << endl;
				return true;
			}

		}
	}

	return false;


}


int scanforvariable(int max_size, string symtable[][2], string instructionset[7][2], int pointer) {

	//string symboltable[pointer][1]; //need to allocate
	//size_t symtablesize=6;
	string in = "";
	//cout << "enter things"<< endl;
	string input;
	cin >> input; //get input
	//cout << input.length()<< endl;
	for (char c : input) {


		//cout<< c<< endl;
		in += c;
		//cout<< in<<endl;
	}
	if (instructionlookup(in, instructionset)) {
		//cout << "this is instruction"<< endl;
		string function = getinstruction(in, instructionset);
		//cout << function;
		out.replace(13, 16, function);
		//cout << out << endl;
		return pointer;
	}

	for (char c : in) {
		if (c == ';') {
			return pointer;

		}

		if (!(isdigit(c))) {
			symtable[pointer][1] += in;
			pointer++;
			return pointer;
		}
	}

	//cout << symtable[pointer][0]<< " ok"<< endl;
	//convert to big-edian binary and output
	string operand = bigendbinary(stoi(in));
	out.replace(0, 5, operand);
	//cout << out<< endl;
	//string padding= getpadding(function,operand);
	//cout<<operand<<"00000000"<<function<<"0000000000000000"<< endl;
	return pointer;


}

void displaysymtable(string symtable[][2], int pointer) {
	// int rows =  sizeof(symtable) / sizeof(symtable[0][0]);
	//cout << symtable[0][1];
	//cout << pointer;
	//cout << symtable[pointer][1];
	for (int i = 1; i < pointer + 1; i++) {
		for (int j = 1; j < 2; j++) {
			cout << symtable[i][j];
			cout << "next" << endl;
		}
	}
	cout << "symtable displayed" << endl;
}






int main() {
	//function takes first part of input and seperates word
	  //enters word into symboltable
	string instructionset[7][2] = {

	{"JMP","000"},
	{"JRP","100"},
	{"LDN","010"},
	{"STO","110"},
	{"SUB","001"},
	{"CMP","011"},
	{"STP","111"}



	};

	int max_size = 6;
	int pointer = 1;

	string symboltable[max_size][2]; //need to allocate
	for (int k = 0; k < 4; k++) {
		pointer = (scanforvariable(max_size, symboltable, instructionset, pointer));

		//cout << out;
	}
	cout << out << endl;
	//scanforvariable(max_size,symboltable,instructionset,pointer);
	//displaysymtable(symboltable,pointer);
	return 0;


}