#include ".\headers\singleGame.h"

#include <iostream>
using namespace std;

// Compile:		g++ -c singleGame.cpp singleGameManual.cpp
// Build:		g++ -o manual.exe singleGame.o singleGameManual.o
// Run:			.\manual.exe

const int STRATEGYAMOUNT = 10;

// A Single Cycle

int main()
{
	int gameSize;
	while (true)
	{
		cout << "Input Game Size (>0): ";
		cin >> gameSize;
		if (gameSize > 0) break;
		
		// Error-Handling
		cout << "[ERROR] Game Size is not a positive integer. \n\n";
	}
	cout << "\n";
	
	int p1[gameSize + 4], p2[gameSize + 4];
	
	for (int i = 0; i < 4; ++i)
	{
		p1[i] = -1;
		p2[i] = -1;
	}
				
	int code1, code2;
	while (true)
	{
		cout << "Input Code 1 (-1 for PvE): ";
		cin >> code1;
		if ((code1 == -1) || (code1 >= 1 && code1 <= STRATEGYAMOUNT)) break;
		
		// Error-Handling
		cout << "[ERROR] Code 1 is out of range. You are only allowed to input -1 or 1~8. \n\n";
	}
	cout << "\n";
	while (true)
	{
		cout << "Input Code 2: ";
		cin >> code2;
		if (code2 >= 1 && code2 <= STRATEGYAMOUNT) break;
		
		// Error-Handling
		cout << "[ERROR] Code 2 is out of range. You are only allowed to input 1~8. \n\n";
	}
	
	if (code1 == -1) // PvE
	{
		cout << "\nInput Your Choice (Separate by whitespace): ";
		for (int i = 4; i < gameSize + 4; ++i) cin >> p1[i];
	}
	cout << "\n";
		
	fullGame(gameSize, code1, code2, p1, p2, true);

	return 0;
}
