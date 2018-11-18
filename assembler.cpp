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


void getcode(string filename) {

	string line;
	ifstream file(filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			filearr.push_back(line);
			cout << line << '\n';
		}
		file.close();
		cout << "file closed" << endl;
	}

	else cout << "Unable to open file";


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

				//cout  << instruset[i][j+1];
				return instruset[i][j + 1];
			}

		}
	}
}

bool instructionlookup(string word, string instruset[7][2]) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 1; j++) {
			if (instruset[i][j] == word) {

				//cout  << instruset[i][j+1] << endl;
				return true;
			}

		}
	}

	return false;


}


int firstscanforvariable(int max_size, string symtable[][2], string instructionset[7][2], int pointer, string in) {

	//string symboltable[pointer][1]; //need to allocate
	//size_t symtablesize=6;
	/*string in="";
	//cout << "enter things"<< endl;
	string input;
	cin >> input ; //get input
	//cout << input.length()<< endl;
	for(char c : input){


			//cout<< c<< endl;
	in+= c;
	//cout<< in<<endl;
	} */
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

			if (in == "VAR") {
				return pointer;

			}
			symtable[pointer][1] += in;
			pointer++;
			return pointer;
		}
	}

	//cout << symtable[pointer][0]<< " ok"<< endl;
	//convert to big-edian binary and output
	symtable[pointer - 1][2] += in;
	string operand = bigendbinary(stoi(in));

	out.replace(0, 5, operand);
	//cout << out<< endl;
	//string padding= getpadding(function,operand);
	//cout<<operand<<"00000000"<<function<<"0000000000000000"<< endl;
	return pointer;


}
bool lookupsymtable(string in, string symtable[][2], int pointer) {
	in += ':';

	for (int i = 0; i < pointer; i++) {
		for (int j = 0; j < 2; j++) {
			if (symtable[i][j] == in) {

				return true;
			}
		}
	}
	return false;

}








string secondscan(string in, string symtable[][2], int pointer) {
	in += ':';
	cout << in << " ok scanning " << endl;
	cout << "pointer is " << endl;
	for (int i = 0; i < pointer; i++) {
		for (int j = 0; j < 2; j++) {
			if (symtable[i][j] == in) {
				cout << "trying " << symtable[i][j] << endl;
				string rep = symtable[i][j + 1];
				return rep;
			}

		}
	}

	return "";




}





void displaysymtable(string symtable[][2], int pointer) {
	// int rows =  sizeof(symtable) / sizeof(symtable[0][0]);
	//cout << symtable[0][1];
	//cout << pointer;
	//cout << symtable[pointer][1];
	for (int i = 1; i < pointer + 1; i++) {
		for (int j = 1; j < 3; j++) {
			cout << symtable[i][j] << endl;
			//cout << "next"<< endl;
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
	string word = "";
	int max_size = 101;
	int pointer = 1;
	getcode("baby.txt");
	string symboltable[max_size][2]; //need to allocate
	int count_file = filearr.size();
	for (string str : filearr) {
		cout << str << endl;
		istringstream iss(str);
		//cout << "here" << endl;
		while (iss >> word) {
			if (word == ";") {
				break;
			}
			//cout << word << endl;
			pointer = (firstscanforvariable(max_size, symboltable, instructionset, pointer, word));
			//cout << pointer << endl;
		}
		cout << out << endl;
	}
	displaysymtable(symboltable, pointer);
	for (string str : filearr) {
		cout << str << endl;
		istringstream iss(str);
		cout << "here" << endl;
		while (iss >> word) {
			if (word == ";") {
				break;
			}
			cout << word << " ok" << endl;
			if (lookupsymtable(word, symboltable, pointer)) {
				cout << "it is " << endl;

				string rep = secondscan(word, symboltable, pointer);
				cout << "rep is " << rep << endl;
				if (!(rep == "")) {
					int front = str.find(word);
					cout << front << endl;
					int back = word.length();
					cout << back << endl;
					cout << "replacing in " << str << endl;
					cout << "here!" << endl;
					cout << rep << endl;
					//rep+=" ;";
					cout << rep << endl;
					str.replace(front, back, rep);
					cout << "new string " << str << endl;
					//filearr2.push_back(str);
				}
			}

		}
		filearr2.push_back(str);

		//(firstscanforvariable(max_size,symboltable,instructionset,pointer,w));
	}/*
	string w="";
	for (string st: filearr2){
	istringstream iss(st);
	//cout << "here" << endl;
	while (iss >> w){
	if (w==";"){
	break;}


	if (instructionlookup(w, instructionset)){
	//cout << "this is instruction"<< endl;
	string function=getinstruction(w, instructionset);
	//cout << function;
	out.replace(13,16,function);

	}
	else{
	string operand= bigendbinary(stoi(w));

	out.replace(0,5,operand);

	//cout << word << endl;

	//cout << pointer << endl;
	}}
	//cout << out<< endl;


	}
	*/
	//pointer=(firstscanforvariable(max_size,symboltable,instructionset,pointer,word));
	//cout << pointer << endl;

	cout << out << endl;








	//cout<< out << endl;
	//scanforvariable(max_size,symboltable,instructionset,pointer);
	//displaysymtable(symboltable,pointer);
	cout << "y" << endl;
	cout << filearr2.size();

	for (int i = 0; i < filearr2.size(); i++) {

		cout << filearr2[i] << endl;
	}
	return 0;


}
