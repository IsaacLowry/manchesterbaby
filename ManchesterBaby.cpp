/*
 * MANCHESTER BABY SIMULATOR
 *
 * Assignment 3
 *
 * AC21008 - Computer Systems 2A - Architecture Fundamentals & Unix
 *
 *
 *
 * Contains all necessary functions required to implement a simulated version of the
 * Manchester Baby Small Scale Electronic Machine (SSEM).
 * Simulation requires 'assembled' machine code file.
 */

//Included libraries and associated files:
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

#include "ManchesterBaby.h"

using namespace std;

////////////////////////////////////////////
/*---------Constructor Methods------------*/

ManchesterBaby::ManchesterBaby(){
	cout << "Manchester Baby Started..." << endl;
	status = "Running";

	CI = 0;

	// Initialise all arrays.
	for(int i =0; i < StoreSize; i++)
	{
		Accumulator[i]=0;
		Control[i]=0;
		temp[i]=0;
		for(int j =0; j < StoreSize; j++)
		{
			Store[i][j] = 0;
		}
	}
}

ManchesterBaby::~ManchesterBaby(){
	cout << "Manchester Baby Stopped..." << endl;
}

////////////////////////////////////////////
/*-----------Accessor Methods--------------*/

bool ManchesterBaby::loadFile(){

	/* File Stream setup */
	string Line;							// String to store line contents
	ifstream binaryFile;					// Input file stream for file to be loaded.
	binaryFile.open ("binaryProgram.txt");

	getline(binaryFile,Line); 				// Reads first line in as string (set as fileLine count) and ignored.
	int lineCount=0;						// Line counter

	istringstream ( Line ) >> lineCount;	// Reads file first line as lineCount.

	cout << "\n Loading Program to Memory"<< endl;


	if(lineCount==0)	{ cout << "\n File 'binaryProgram.txt' does either not exist or cannot be loaded!" << endl; }
	else				{ cout << " Transferring " << lineCount << " lines to memory.\n" << endl; }

	/* loop throgh the lines of the file */
	int linesLoaded = 0;

	while(getline (binaryFile, Line)){
		linesLoaded++;

		cout << " " << Line; 				// Prints current line.

		/*Increments through each line and saves each char in relevant store element */
		for(int i=0; i <=31; i++) {
			char bit = Line.at(i);

			if(bit=='1')	{ Store[linesLoaded][i]= 1; }
			else			{ Store[linesLoaded][i]= 0; }
		}

	    cout << endl;
	}

	binaryFile.close();						// Close filestream

	/* Checks correct amount of lines have been loaded successfully */
	if(linesLoaded==(lineCount)) 	{ cout << "\n Program loaded sucessfully" << endl; return true; }
	else							{ cout << "\n Error occured loading file - Line "<<lineCount << endl; }
	return false;
}

void ManchesterBaby::IncrementCI(){
	/*Ensures Control Instruction doesn't exceed 32 as is 32bit memory store */
	if(CI<31){
		CI++;	
	}
}

void ManchesterBaby::Fetch(int CI){

	cout << "\n\nFETCH" << endl;

	/* Copy and display current instruction */
	cout << " Present Instruction = ";
	for(int i=0; i <32; i++)
	{
		Control[i] = Store[CI][i];
		cout << Control[i];
	}
}

string ManchesterBaby::Decode(){

	cout << "\n\nDECODE" << endl;
	string opcode = " ";

	stringstream ss; // Blank stringstream to store decimal opcode as string.

	// Control array elements 13-16 are appended one at a time to the string stream ss.
	for(int i = 13; i <16; i++)
	{
		int t = Control[i];
		ss << t;
		opcode = ss.str();
	}

	// converts address opcode into function number
	cout << " Decode Instruction Code =  " << opcode << endl;

	if 		(opcode == "000") { cout << " Instruction Code = JMP" << endl; opcode = "JMP";}
	else if (opcode == "100") { cout << " Instruction Code = JRP" << endl; opcode = "JRP";}
	else if (opcode == "010") { cout << " Instruction Code = LDN" << endl; opcode = "LDN";}
	else if (opcode == "110") { cout << " Instruction Code = STO" << endl; opcode = "STO";}
	else if (opcode == "001") { cout << " Instruction Code = SUB" << endl; opcode = "SUB";}
	else if (opcode == "101") { cout << " Instruction Code = SUB" << endl; opcode = "SUB";}
	else if (opcode == "011") { cout << " Instruction Code = CMP" << endl; opcode = "CMP";}
	else if (opcode == "111") { cout << " Instruction Code = STP" << endl; opcode = "STP";}

	return opcode;
}

int ManchesterBaby::Execute(string opcode){
	
	cout << "\nEXECUTE" << endl;
	
	/* Extract address operand from current instruction */
	int operand=0;
	int array[5]={1,2,4,8,16};
	for(int i=0; i<5; i++)
	{
		operand=operand+Control[i]*array[i];
	}

	cout << " Operand Address = " << operand << endl;

	/* Execute relevant instruction */
	if 		(opcode == "JMP") { JMP(operand); }
	else if (opcode == "JRP") { JRP(operand); }
	else if (opcode == "LDN") { LDN(operand); }
	else if (opcode == "STO") { STO(operand); }
	else if (opcode == "SUB") { SUB(operand); }
	else if (opcode == "SUB") { SUB(operand); }
	else if (opcode == "CMP") { CMP(); }
	else if (opcode == "STP") { STP(); }

	cout << endl;

	return 0;
}

void ManchesterBaby::Display(){

	/* Display method adapted from:
	 * https://github.com/apoclyps/SoC-Manchester-Baby
	 */

	cout << "\n" << " STORE" << endl;
	cout << "       Operand     " << "     Memory Bits 1-8     " << " Opcode " << "  Memory Bits 9-32 " << endl;
	cout << "    <------------->" << " <--------------------->" << " <------>" << " <--------------------------------------------->" <<  endl;
	cout << "                    1  2  4  8 16 32 64 128          1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16  " << endl;
	cout << "     1  2  4  8 16                          1  2  4  " << endl;

	for(int i = 0; i < 32; ++i){
		if((i)<10)						{ cout << " " << (i) << "  "; }
		else							{ cout << " " << (i) << " "; }

		for(int j = 0; j < 32; ++j){ 
			if(Store[i][j] == 0) 		{ cout << " . "; }
			else if(Store[i][j] == 1) 	{ cout << " | "; }
		}
		cout << endl;
	}
	cout << endl;

	cout << "\n\n" << " ACCUMULATOR" << endl;
	cout << "      Operand      " << "   Memory Bits 1-8        " << " Opcode " << "  Memory Bits 9-32 " << endl;
	cout << "    <------------->" << " <--------------------->" << " <------>" << " <--------------------------------------------->" <<  endl;
	cout << "                    1  2  4  8 16 32 64 128          1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16  " << endl;
	cout << "     1  2  4  8 16                          1  2  4  " << endl;
	cout << "    ";

	for(int i = 0; i < 32; ++i){
		if(Accumulator[i] == 0)			{ cout << " . "; }
		else if(Accumulator[i] == 1)	{ cout << " | "; }
	}
	cout << endl;


	cout << "\n\n" << " CONTROL" << endl;
	cout << "      Operand      " << "   Memory Bits 1-8        " << " Opcode " << "  Memory Bits 9-32 " << endl;
	cout << "    <------------->" << " <--------------------->" << " <------>" << " <--------------------------------------------->" <<  endl;
	cout << "                    1  2  4  8 16 32 64 128          1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16  " << endl;
	cout << "     1  2  4  8 16                          1  2  4  " << endl;

	// current instruction
	cout << " CI ";
	for(int i = 0; i < 32; ++i){
		if(Control[i] == 0)				{ cout << " . "; }
		else if(Control[i] == 1)		{ cout << " | "; }
	}
	cout << endl;

	// Present instruction only displayed when the machine is running
	if(status=="Running")
	{
		cout << " PI ";
		for(int i = 0; i < 32; ++i) {
			if(Control[i] == 0) 		{ cout << " . "; }
			else if(Control[i] == 1) 	{ cout << " | "; }
		}
	}
	cout << "    <------------->" << " <--------------------->" << " <------>" << " <--------------------------------------------->" <<  endl;
	cout << "____________________________________________________________________________________________________" <<  endl;
	cout << endl;
}

int ManchesterBaby::convertBinaryToDecimal(int array[]){

	int decimalNum = 0;

	// Creates and instantiates array with 32 elements
	int valueCI[32];
	for (int i=0; i<32; i++){
		valueCI[i] = pow(2,i);
	}

	// Creates decimal number of binary value.
	for (int i=0; i<31; i++){
		decimalNum = decimalNum + array[i]*valueCI[i];
	}

	// Negates value according to designated array element value.
	if(array[31]!=0){
		decimalNum = -decimalNum;		
	}

    return decimalNum;
}

void ManchesterBaby::convertDecimalToBinary(int decimal){

	cout << "Decimal Value = " << decimal << endl;

	// Sets Positive/Negative assignment value
	if(decimal < 0){
		temp[31] = 1;
		decimal = -decimal;
	}

	/*
	Converts passed integer from decimal to binary and stores in Accumulator[] array.
	Achieved through bitwise comparison of k and 1 (0001), using the counter to
	right shift the operator (0 shifts on first loop (Big Endian)). If the Least Significant Bit (LSB) is
	1, 1 is set to Accumulator[i]. 0 being set for false result comparisons.
	*/
	int k;
	for (int i = 0; i <31; i++){
		k = decimal >> i;

		if (k & 1)	{ temp[i] = 1; } 
		else		{ temp[i] = 0; }
	}
}

////////////////////////////////////////////
/*---------Instruction Functions----------*/

void ManchesterBaby::JMP(int line){

	// Copy contents of the specifed line into the Control
	for(int i = 0; i < 32; i++)
	{
		Control[i]=Store[line][i];
	}

	CI = line;
}

void ManchesterBaby::JRP(int line){

	// Sets number to value of line to be executed.
	for(int i = 0; i < 32; i++)
	{
		temp[i]=Store[line][i];
	}

	if(temp[31] == 0){
		temp[31] = 1;
	} else temp[31] = 0;

	int currentNum = convertBinaryToDecimal(temp);

	int result = CI + currentNum;

	JMP(result);
}

void ManchesterBaby::LDN(int line){

	IncrementCI();

	// Sets Accumulator to value of line to be executed.
	for(int i = 0; i < 32; i++)
	{
		Accumulator[i]=Store[line][i];
	}

	// Sets designated array element to signify negation.
	if(Accumulator[31] == 0){
		Accumulator[31] = 1;
	} else Accumulator[31] = 0;
}

void ManchesterBaby::STO(int line){

	IncrementCI();

	// Stores Accumulator value into specified store address.
	for(int i = 0; i < 32; i++)
	{
		Store[line][i]=Accumulator[i];
	}
}

void ManchesterBaby::SUB(int line){

	// Sets number to value of line to be executed.
	for(int i = 0; i < 32; i++)
	{
		temp[i]=Store[line][i];
	}

	if(temp[31] == 0){
		temp[31] = 1;
	} else temp[31] = 0;

	// Convert values to decimal, computes answer, then loads to accumulator.
	int currentNum = convertBinaryToDecimal(temp);
	int accumNum = convertBinaryToDecimal(Accumulator);

	int result = accumNum + currentNum;

	convertDecimalToBinary(result);

	for(int j=0; j<31; j++){
		Accumulator[j] = temp[j];
	}

	IncrementCI();
}

void ManchesterBaby::CMP(){
	
	int accumNum = convertBinaryToDecimal(Accumulator);

	if (accumNum < 0){
		IncrementCI();
		IncrementCI();
	} else IncrementCI();
}

void ManchesterBaby::STP(){
	status = "Stopped";
}

int main()
{
	ManchesterBaby ManchesterBaby;
	ManchesterBaby.loadFile();
	ManchesterBaby.IncrementCI();

	while(ManchesterBaby.status != "Stopped"){
		usleep(500000);
		cout << "\033[2J\033[1;1H";
		ManchesterBaby.Fetch(ManchesterBaby.CI);
		ManchesterBaby.Execute(ManchesterBaby.Decode());
		ManchesterBaby.Display();
	}

	return 0;
}
