#include ".\headers\singleGame.h"

#include <iostream>
#include <utility>
using namespace std;

// Compile:		g++ -c singleGame.cpp expGenerate.cpp
// Build:		g++ -o exp.exe singleGame.o expGenerate.o
// Run:			.\exp.exe

int main()
{
	// Reverse Copycat
	for (int i = 1; i <= 9; ++i) startCycle(20, 9, i, true);
	
	// Detective Pro
	for (int i = 1; i <= 10; ++i) startCycle(20, 10, i, true);
	
	// Detective Pro Max
	for (int i = 1; i <= 11; ++i) startCycle(20, 11, i, true);
}
