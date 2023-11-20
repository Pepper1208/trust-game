#include <iostream>
#include <string>
#include <utility>
#include <random>
#include <map>
using namespace std;

// For Random Number Generator Purpose
default_random_engine generator;
uniform_int_distribution<int> distribution(1, 10);

/*
 * Code for each strategies (personalities):
 * -1 Manual		Manual Input.
 * 1 Cooperator		Always Cooperate.
 * 2 Cheater		Always Cheat.
 * 3 Copycat		Cooperate in the first round.
 * 					Copy enemy's last move every time.
 * 4 Grunder		Always cooperate until enemy cheats.
 * 					Then, always cheat.
 * 5 Detective		Start with Cooperate, Cheat, Cooperate, Cooperate. 
 * 					If enemy cheats back, act like COPYCAT.
 * 					If enemy never cheats back, act like CHEATER.
 * 6 Copykitten		Act like COPYCAT.
 * 					However, only cheat when enemy cheats twice.
 * 7 Simpleton		Start with Cooperate.
 * 					If enemy cooperate, do the same thing as last move.
 * 					If enemy cheat, do the opposite thing as last move.
 * 8 Random			Cooperate or Cheat with a 50/50 chance.
 */

map<int, string> codeMap = {
		{ -1, "Player"}, 
		{ 1, "Cooperator" },
		{ 2, "Cheater" }, 
		{ 3, "Copycat" }, 
		{ 4, "Grunder" }, 
		{ 5, "Detective" },
		{ 6, "Copykitten" },
		{ 7, "Simpleton" },
		{ 8, "Random" }
};

void printCodeInstruction()
{
	cout << "Code for each strategies (personalities): \n"; 
	cout << "-1 Manual        Manual Manual Input.\n";
	cout << "1 Cooperator     Always Cooperate.\n";
	cout << "2 Cheater        Always Cheat.\n";
	cout << "3 Copycat        Cooperate in the first round.\n";
	cout << "                 Copy enemy's last move every time.\n";
	cout << "4 Grunder        Always cooperate until enemy cheats.\n";
	cout << "                 Then, always cheat.\n";
	cout << "5 Detective      Start with Cooperate, Cheat, Cooperate, Cooperate.\n";
	cout << "                 If enemy cheats back, act like COPYCAT.\n";
	cout << "                 If enemy never cheats back, act like CHEATER.\n";
	cout << "6 Copykitten     Act like COPYCAT.\n";
	cout << "                 However, only cheat when enemy cheats twice.\n";
	cout << "7 Simpleton      Start with Cooperate.\n";
	cout << "                 If enemy cooperate, do the same thing as last move.\n";
	cout << "                 If enemy cheat, do the opposite thing as last move.\n";
	cout << "8 Random         Cooperate or Cheat with a 50/50 chance.\n";
	cout << "\n";
}

pair<int, int> gameRes(int a, int b)
{
	if (a == 1 && b == 1) return make_pair(2, 2);
	if (a == 1 && b == 0) return make_pair(-1, 3);
	if (a == 0 && b == 1) return make_pair(3, -1);
	if (a == 0 && b == 0) return make_pair(0, 0);
	
	// Error-Handling
	cout << "[ERROR] Out of range when calculating results of a game. \n";
	return make_pair(-99999, -99999);
}

pair<int, int> playGame(int gameSize, int p1[], int p2[])
{
	int v1 = 0, v2 = 0;
	for (int i = 4; i < gameSize + 4; ++i)
	{
		v1 += gameRes(p1[i], p2[i]).first;
		v2 += gameRes(p1[i], p2[i]).second;
	}
	
	return make_pair(v1, v2);
}

int determine(int code, int currentIndex, int lastEMove, int last2EMove, int lastMove, int sumFirst4EMove)
{
	switch (code)
	{
		case 1: // Cooperator
			return 1;
			
		case 2: // Cheater
			return 0;
			
		case 3: // Copycat
			return currentIndex == 0 ? 1 : lastEMove;
			
		case 4: // Grunder
			return (lastMove == 0 || lastEMove == 0) ? 0 : 1;
			
		case 5: // Detective
			
			// First Four Moves
			if (currentIndex == 0 || currentIndex == 2 || currentIndex == 3) return 1;
			if (currentIndex == 1) return 0;
			
			// After Moves
			if (sumFirst4EMove == 4) return 0; else return lastEMove;
			
		case 6: // Copykitten
			return (lastEMove == 0 && last2EMove == 0) ? 0 : 1;
			
		case 7: // Simpleton
			if (currentIndex == 0) return 1;
			if (lastEMove == 1)
			{
				return lastMove;
			} else
			{
				return lastMove == 1 ? 0 : 1;
			}
			
		case 8: // Random
			return distribution(generator) % 2;
			
		default: // Error-Handling
			cout << "[ERROR] Strategy Code is out of range. \n";
			return -1;
	}
}

void fullGame(int gameSize, int code1, int code2, int p1[], int p2[])
{
	int first4move1 = 0, first4move2 = 0;
	for (int i = 4; i < gameSize + 4; ++i)
	{
		if (i == 8)
		{
			first4move1 = p1[4] + p1[5] + p1[6] + p1[7];
			first4move2 = p2[4] + p2[5] + p2[6] + p2[7];
		}
		
		if (code1 != -1) p1[i] = determine(code1, i-4, p2[i-1], p2[i-2], p1[i-1], first4move2);
		p2[i] = determine(code2, i-4, p1[i-1], p1[i-2], p2[i-1], first4move1);
	}
	
	cout << codeMap.at(code1) << " vs " << codeMap.at(code2) << "\n\n";
	
	cout << "Player 1: ";
	for (int i = 4; i < gameSize + 4; ++i) cout << p1[i] << " ";
	cout << "\n";
	cout << "Player 2: ";
	for (int i = 4; i < gameSize + 4; ++i) cout << p2[i] << " ";
	cout << "\n\n";
	
	pair<int, int> res = playGame(gameSize, p1, p2);
	cout << "Player 1 Score: " << res.first << "\n";
	cout << "Player 2 Score: " << res.second << "\n";
}

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
		
	printCodeInstruction();
		
	int code1, code2;
	while (true)
	{
		cout << "Input Code 1 (-1 for PvE): ";
		cin >> code1;
		if ((code1 == -1) || (code1 >= 1 && code1 <= 8)) break;
		
		// Error-Handling
		cout << "[ERROR] Code 1 is out of range. You are only allowed to input -1 or 1~8. \n\n";
	}
	cout << "\n";
	while (true)
	{
		cout << "Input Code 2: ";
		cin >> code2;
		if (code2 >= 1 && code2 <= 8) break;
		
		// Error-Handling
		cout << "[ERROR] Code 2 is out of range. You are only allowed to input 1~8. \n\n";
	}
	
	if (code1 == -1) // PvE
	{
		cout << "\nInput Your Choice (Separate by whitespace): ";
		for (int i = 4; i < gameSize + 4; ++i) cin >> p1[i];
	}
	cout << "\n";
		
	fullGame(gameSize, code1, code2, p1, p2);

	return 0;
}
