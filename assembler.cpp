/**
  * Project: AC21009 (Computer Systems 2A) Assignment 3 - Small Scale Experimental Machine (SSEM)/'Manchester Baby'
  * Subtitle: Manchester Baby Simulator
  * Name: Jason Khan 180024391 for Team 16
  * Date: 17/11/2018
  * Assembler for Manchester Baby.
**/
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <utility>
#include <fstream>
#include <vector>
using namespace std;
//global variable final output
string out = "00000000000000000000000000000000";
vector<string> filearr;
vector<string>filearr2;
string bigendbinary(int i) {
	string num = "";
	while (i != 0) {

		num += to_string(i % 2);
		//cout<< num<< endl;
		i = i / 2;

	}
	return num;

}




bool isnumber(string str) {
	for (char c : str) {

		if (!(isdigit(c))) {

			return false;

		}
	}
	return true;
}








void getcode(string filename) {

	string line;
	ifstream file(filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			filearr.push_back(line);
			//cout << line << '\n';
		}
		file.close();
		//cout<< "file closed" << endl;
	}

	else cout << "Cannot open file." << endl;


}


int getstart() {
	string st = "START:";
	for (int j = 0; j < static_cast<int>(filearr.size()); j++) {
		//cout << filearr[j]<< endl;
		string big = filearr[j];
		if (big.find(st) != string::npos) {
			int k = j;
			return k;
		}
	}
	return 0;

}


int getnumcomm() {
	int count = 0;
	int k = getstart();
	for (int t = k; t < static_cast<int>(filearr.size()); t++) {
		string prt = filearr[t];
		if (prt[0] == ';') {

			count++;
		}


	}
	return count;
}





int getlinenum(string in) {
	int k = getstart();
	int count = getnumcomm();
	//cout<<count;
	in += ':';
	for (int i = 0; i < static_cast<int>(filearr.size()); i++) {
		//cout << filearr[i]<< endl;
		string big = filearr[i];
		if (big.find(in) != string::npos) {
			int val = (((i + 1) - k) - count);

			//cout << val << endl;


			return val;
		}
	}

	return 0;
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
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 1; j++) {
			if (instruset[i][j] == word) {

				//gets opcode from instruction set

				return instruset[i][j + 1];
			}

		}
	}
	return "";
}

bool instructionlookup(string word, string instruset[7][2]) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 1; j++) {
			if (instruset[i][j] == word) {


				return true;
			}

		}
	}

	return false;


}


int firstscanforvariable(string symtable[][2], string instructionset[7][2], int pointer, string in) {

	if (instructionlookup(in, instructionset)) {
		cout << "Instruction found" << endl;
		string function = getinstruction(in, instructionset);

		out.replace(13, 3, function);
		cout << out << endl;
		return pointer;
	}

	for (char c : in) {
		if (c == ';') {
			return pointer;

		}

		if (!(isdigit(c))) {

			if (in == "VAR") {
				return pointer;

			}
			cout << "Adding to symbol table" << endl;
			symtable[pointer][1] += in;
			pointer++;
			return pointer;
		}
	}


	//convert to big-edian binary and output
	symtable[pointer - 1][2] += in;
	string operand = bigendbinary(stoi(in));
	out.replace(0, 5, operand);
	cout << "Adding value to symbol table" << endl;


	return pointer;


}
bool lookupsymtable(string in, string symtable[][2], int pointer) {
	in += ':';

	for (int i = 0; i < pointer; i++) {
		for (int j = 0; j < 2; j++) {
			if (symtable[i][j] == in) {
				cout << "Found in symbol table" << endl;
				return true;
			}
		}
	}
	return false;

}








string secondscan(string in) {
	cout << "Replacing variables" << endl;
	int rep = getlinenum(in);
	string rep2 = to_string(rep);
	return rep2;
}











string finalconversion(string instructionset[7][2], string in, string out) {
	//check to see if word is in instruction set
	if (instructionlookup(in, instructionset)) {
		//obtain opcode
		string function = getinstruction(in, instructionset);
		cout << "instruction found, opcode obtained" << endl;
		//update output buffer
		out.replace(13, 3, function);
		cout << out << endl;
		return out;
	}
	for (char c : in) {
		//check for certain flags e.g. comments
		if (c == ';') {
			//cout<< out << endl;

			return out;

		}
		if (!(isdigit(c))) {

			//ignore other terms
			return out;

		}
	}

	string operand = bigendbinary(stoi(in));

	out.replace(0, operand.length(), operand);

	return out;
}


void displaysymtable(string symtable[][2], int pointer) {
	//not for assembler--> useful function for displaying symbol table
	for (int i = 1; i < pointer + 1; i++) {
		for (int j = 1; j < 3; j++) {
			cout << symtable[i][j] << endl;

		}
	}
	cout << "symtable displayed" << endl;
}






int main(int argc, char** argv) {
	//define instruction set
	string instructionset[7][2] = {

	{"JMP","000"},
	{"JRP","100"},
	{"LDN","010"},
	{"STO","110"},
	{"SUB","001"},
	{"CMP","011"},
	{"STP","111"}



	};
	//check arguments
	if (argc != 2) {
		cout << "Please enter filename only as argument" << endl;
		return 1;
	}
	//set variables
	string word = "";

	int pointer = 1;
	string file = argv[1];
	//obtain code from file
	getcode(file);
	string symboltable[101][2]; //initialise empty symboltable


	cout << "Starting first pass.." << endl;

	for (string str : filearr) {
		//scan through each line of file
		istringstream iss(str);
		//check each word
		while (iss >> word) {
			if (word == ";") {
				break;
			}
			//call function to scan and fill symbol table
			pointer = (firstscanforvariable(symboltable, instructionset, pointer, word));
			//displaysymtable(symboltable,pointer);
		}

	}
	cout << "Symbol table complete" << endl;
	for (string str : filearr) {

		istringstream iss(str);

		while (iss >> word) {
			if (word == ";") {
				break;
			}



			if (lookupsymtable(word, symboltable, pointer)) {

				//if word in symboltable, obtain address and replace
				string rep = secondscan(word);

				if (!(rep == "")) {
					int front = str.find(word);

					int back = word.length();

					str.replace(front, back, rep);

				}
			}
			else if ((!(word.find(":") != string::npos))) {
				//&&(!(instructionlookup(word,instructionset)))&&(!(lookupsymtable(word,symboltable,pointer)))){
				string wo = word;
				wo += ":";
				if ((!(instructionlookup(word, instructionset))) && (!(lookupsymtable(wo, symboltable, pointer))) && (word != "VAR") && (!(isnumber(word)))) {
					cout << "Syntax Error-" << word << " Variable not Declared" << endl;
					return 2;
				}
			}
		}
		cout << "Variables replaced" << endl;
		filearr2.push_back(str);

	}

	ofstream outfile;
	outfile.open("binarycode.txt");

	cout << "starting second pass.." << endl;
	for (string str : filearr2) {
		//decalre default buffer
		out = "00000000000000000000000000000000";
		istringstream iss(str);

		while (iss >> word) {
			if (word != ";") {

				out = finalconversion(instructionset, word, out);

			}

			else {
				break;
			}

		}
		char comp = str[0];
		if ((comp != ';') && (str != "")) {
			//write to file
			cout << out << endl;

			outfile << out;
			outfile << "\n";


		}


	}
	//close file and exit
	cout << "Binary Written to file binarycode.txt." << endl;
	outfile.close();

	return 0;


}
