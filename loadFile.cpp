#include <vector>
#include <iostream>
#include <fstream>
#include "mancbaby.h"


int MancBaby :: loadFromFile() {
	string filePath;
	cout << "Please enter name of file to load program from: ";
	cin << filePath;
	fstream readFile;

	readFile.open(filePath, ios::in);
	string currLine;
	if (readFile.isOpen()) {
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
