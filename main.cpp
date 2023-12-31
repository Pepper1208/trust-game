#include ".\headers\singleGame.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

// Compile:		g++ -c singleGame.cpp main.cpp
// Build:		g++ -o main.exe singleGame.o main.o
// Run:			.\main.exe

const int STRATEGYAMOUNT = 11;

/*
 * Code for each strategies (personalities):
 * -1	Manual				Manual Input.
 * 1	Cooperator		  	Always Cooperate.
 * 2	Cheater		  		Always Cheat.
 * 3	Copycat		  		Cooperates in the first round.
 * 					 	 	Copies enemy's last move every time.
 * 4	Grudger		  		Always cooperate until enemy cheats.
 * 					  		Then, always cheat.
 * 5	Detective		  	Starts with Cooperate, Cheat, Cooperate, Cooperate. 
 * 					  		If enemy cheats back, act like COPYCAT.
 * 					  		If enemy never cheats back, act like CHEATER.
 * 6	Copykitten		  	Acts like COPYCAT.
 * 					  		However, only cheat when enemy cheats twice.
 * 7	Simpleton		  	Starts with Cooperate.
 * 					  		If enemy cooperate, do the same thing as last move.
 * 					  		If enemy cheat, do the opposite thing as last move.
 * 8	Random				Cooperates or Cheats with a 50/50 chance.
 * 
 * [Experimental Strategies(Personalities)]
 * 
 * 9 	Reverse copycat     Cheats in the first round.
 *                       	Copies the opposite move of the enemy's last move every time.
 * 10	Detective Pro		Starts with Cheat, Cooperate, Cheat.
 * 							If the opponent cooperates all the time, acts like Cooperator.
 * 							If the opponent If the opponent cheats all the time, then acts like Cheater.
 * 							If the opponent cooperates twice and cheats once, cooperates in the fourth round and acts like Copycat.
 * 							If the opponent cooperates once and cheats twice, cheats in the fourth round and acts like Copycat.
 * 11	Detective Pro Max	Same as Detective Pro, but starts with Cooperate, Cheat, Cooperate.
 */

void singleLoop(int population, int code[], int res[], int gameSize, int elimAndReplace = 5)
{
	/*
	 * Cycle:
	 * 1. Battle
	 * 2. Eliminate lowest 5 players and Clone 5 top players into the game
	 * 3. Order the player by their code
	 */

	// Step 1: Battle
	
	for (int i = 0; i < population - 1; ++i)
	{
		for (int j = i + 1; j < population; ++j)
		{
			pair<int, int> gameRes = startCycle(gameSize, code[i], code[j], false);
			//~ cout << gameRes.first << " " << gameRes.second << "\n\n";
			res[i] += gameRes.first;
			res[j] += gameRes.second;
		}
	}

	cout << "Game Result: \n";
	// for (int k = 0; k < population; ++k) printf("%-5d ", code[k]);
	for (int k = 0; k < population; ++k) printf("%-3d ", code[k]);
	cout << "\n";
	// for (int k = 0; k < population; ++k) printf("%-5d ", res[k]);
	for (int k = 0; k < population; ++k) printf("%-3d ", res[k]);
	cout << "\n\n";
	
	// Step 2: Elimination and Clone
	
	int eliminateIndex[elimAndReplace] = {0};
	int cloneIndex[elimAndReplace] = {0};
	for (int i = 0; i < elimAndReplace; ++i)
	{
		eliminateIndex[i] = i;
		cloneIndex[i] = i;
	}
	for (int i = elimAndReplace + 1; i < population; ++i)
	{
		for (int j = 0; j < elimAndReplace; ++j)
		{
			if (res[i] < res[eliminateIndex[j]])
			{
				eliminateIndex[j] = i;
				break;
			}
		}
		for (int j = 0; j < elimAndReplace; ++j)
		{
			if (res[i] > res[cloneIndex[j]])
			{
				cloneIndex[j] = i;
				break;
			}
		}
	}
	
	//~ for (int k = 0; k < elimAndReplace; ++k) cout << eliminateIndex[k] << " ";
	//~ cout << "\n";
	//~ for (int k = 0; k < elimAndReplace; ++k) cout << cloneIndex[k] << " ";
	//~ cout << "\n";
	
	vector<int> eliminateList;
	vector<int> cloneList;
	for (int i = 0; i < elimAndReplace; ++i) eliminateList.push_back(eliminateIndex[i]);
	for (int i = 0; i < elimAndReplace; ++i) cloneList.push_back(cloneIndex[i]);
	
	int minIndex = eliminateList[elimAndReplace - 1], maxIndex = cloneList[elimAndReplace - 1];
	
	for (int i = minIndex + 1; i < population; ++i)
	{
		if (res[i] == res[minIndex]) eliminateList.push_back(i);
	}
	for (int i = maxIndex + 1; i < population; ++i)
	{
		if (res[i] == res[maxIndex]) cloneList.push_back(i);
	}
	
	// Shuffle the list
	random_shuffle(eliminateList.begin(), eliminateList.end());
	random_shuffle(cloneList.begin(), cloneList.end());
	
	//~ for (auto it = eliminateList.begin(); it != eliminateList.end(); ++it) cout << *it << " ";
	//~ cout << "\n";
	//~ for (auto it = cloneList.begin(); it != cloneList.end(); ++it) cout << *it << " ";
	//~ cout << "\n\n";
	
	for (int i = 0; i < elimAndReplace; ++i)
	{
		eliminateIndex[i] = eliminateList[i];
		cloneIndex[i] = cloneList[i];
	}
	
	//~ for (int k = 0; k < elimAndReplace; ++k) cout << eliminateIndex[k] << " ";
	//~ cout << "\n";
	//~ for (int k = 0; k < elimAndReplace; ++k) cout << cloneIndex[k] << " ";
	//~ cout << "\n\n";
	
	cout << "Elimination Codes: ";
	for (int i = 0; i < elimAndReplace; ++i) cout << code[eliminateIndex[i]] << " ";
	cout << "\n";
	
	cout << "Clone Codes: ";
	for (int i = 0; i < elimAndReplace; ++i) cout << code[cloneIndex[i]] << " ";
	cout << "\n\n";
	
	for (int k = 0; k < elimAndReplace; ++k) code[eliminateIndex[k]] = code[cloneIndex[k]];
	//~ for (int k = 0; k < population; ++k) cout << code[k] << " ";
	//~ cout << "\n\n";
	
	// Step 3: Reorder the code list
	
	sort(code, code + population);
	cout << "Updated Players: \n";
	// for (int k = 0; k < population; ++k) printf("%-5d ", code[k]);
	for (int k = 0; k < population; ++k) printf("%-3d ", code[k]);
	cout << "\n\n";

}

int main()
{
	int population;
	while (true)
	{
		cout << "Input the population: ";
		cin >> population;
		if (population >= 10) break;
		
		// Error-Handling
		cout << "\033[1;31m[ERROR] The population must be a positive integer bigger or equal than 10. \n\n";
		cout << "\033[1;0m";
	}
	cout << "\n";
	
	//~ cout << population << "\n\n";
	
	int tempStoring[STRATEGYAMOUNT];
	int temp; // Storing the input amount of population
	while (true)
	{
		temp = 0;
		cout << "Please fill in 9 numbers. \nEach number represent different amount of strategies.\n";
		cout << "For example, 1 2 3 0 0 0 0 0 0 means 1 cooperator, 2 cheaters and 3 copycats in the game.\n";
		cout << "Sum of the 9 numbers must be the same as the population input before.\n";
		cout << "Modify the types of population (Separate by space): ";
		for (int i = 0; i < STRATEGYAMOUNT; ++i)
		{
			cin >> tempStoring[i];
			temp += tempStoring[i];
		}
		if (temp == population) break;
		//~ cout << temp;
		
		// Error-Handling
		cout << "\033[1;31m[ERROR] Difference between two inputs of amount of population. \n\n";
		cout << "\033[1;0m";
	}
	int playersCode[population];
	int playersRes[population];
	int flag = 0;
	while (temp > 0)
	{
		for (int i = 0; i < STRATEGYAMOUNT; ++i)
		{
			for (int _ = 0; _ < tempStoring[i]; ++_)
			{
				playersCode[flag] = i + 1;
				flag++; temp--;
			}
		}
	}
	
	cout << "\n";
	int gameSize;
	while (true)
	{
		cout << "Input Game Size (How many rounds per match for each 2 players?): ";
		cin >> gameSize;
		if (gameSize > 0) break;
		
		// Error-Handling
		cout << "\033[1;31m[ERROR] Game Size is not a positive integer. \n";
		cout << "\033[1;0m";
	}
	
	//~ for (int i = 0; i < population; ++i) cout << playersCode[i] << " ";
	//~ cout << "\n\n";
	
	cout << "\n";
	int loopAmount;
	while (true)
	{
		cout << "Input Amount of Cycles (How many tournaments?): ";
		cin >> loopAmount;
		if (loopAmount > 0) break;
		
		// Error-Handling
		cout << "\033[1;31m[ERROR] Amount of cycles is not a positive integer. \n\n";
		cout << "\033[1;0m";
	}
	
	// Game
	
	cout << "\n";
	for (int i = 1; i <= loopAmount; ++i)
	{
		cout << "\033[1;32m[Cycle " << i << "]\n\n" << "\033[1;0m";
		for (int j = 0; j < population; ++j) playersRes[j] = 0;
		singleLoop(population, playersCode, playersRes, gameSize);
	}
			
	return 0;
}
