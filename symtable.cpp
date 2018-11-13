//assemb symbol table
#include <string>
#include <cctype>
#include <iostream>
using namespace std;


int main(){
	//function takes first part of input and seperates word
	//enters word into symboltable
string symboltable[6][2]; //need to allocate
size_t symtablesize=6;
string in="";
cout << "enter things"<< endl;
string input;
cin >> input ; //get input

for(char &c : input){

	if (isspace(c)){

		cout<<"space";
	}
	cout<< c<< endl;
in+= c;
}
symboltable[symtablesize][1]+=in ;
cout << symboltable[symtablesize][1]<< " ok"<< endl;;

return 0;}