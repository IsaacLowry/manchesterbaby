/*
 * MANCHESTER BABY SIMULATOR
 *
 * Assignment 3
 *
 * AC21008 - Computer Systems 2A - Architecture Fundamentals & Unix
 *
 *
 * Defines functions required to implement a simulated version of the
 * Manchester Baby Small Scale Electronic Machine (SSEM).
 */

//Included libraries and associated files:
#include <iostream>
#include <string>
// #include <bitset> - couldn't get to reliably work.

#ifndef _MANCHESTER_BABY_H
#define _MANCHESTER_BABY_H

using namespace std;

// global varaibles for setting the size of memory
const int StoreSize = 32;
const int AccumSize = 32;
const int CtrlSize = 32;


class ManchesterBaby{
	public:

		//Constructor
		ManchesterBaby();
		~ManchesterBaby();

		// Accessor Methods
		bool loadFile();
		void IncrementCI();
		void Fetch(int ci);
		string Decode();
		int Execute(string opcode);
		void Display();
		int convertBinaryToDecimal(int array[]);
		void convertDecimalToBinary(int decimal);

		// instruction functions
		void JMP(int Line);
		void JRP(int Line);
		void LDN(int Line);
		void STO(int Line);
		void SUB(int line);
		void CMP();
		void STP();

		//Class Variables
		int Store[StoreSize][StoreSize];	// main memory
		int Accumulator[AccumSize];			// arithmetic register - holds results of arithmetic operations
		int Control[CtrlSize];				// Present Instruction - current instruction stored
		int temp[CtrlSize];
		int CI;								// Control Instruction - Program counter, contains address (line number) of an instruction in the store
		string status;
};
#endif