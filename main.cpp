#include ".\headers\singleGame.h"

#include <iostream>
using namespace std;

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

const int STRATEGIESNUM = 8;

int main()
{
	// For a single cycle with 2 strategies
	
	//~ startCycle(15, 1, 1);
	//~ startCycle(15, 1, 2);
	//~ startCycle(15, 2, 2);
	
	// Manual Debugging
	
	int population;
	while (true)
	{
		cout << "Input the population: ";
		cin >> population;
		if (population > 1) break;
		
		// Error-Handling
		cout << "[ERROR] The population must be a positive integer bigger than 1. \n\n";
	}
	cout << population << "\n\n";
	
	int playersCode[STRATEGIESNUM];
	int playersRes[STRATEGIESNUM] = {0};
	
	int temp; // Storing the input amount of population
	
	while (true)
	{
		temp = 0;
		cout << "Modify the types of population: ";
		for (int i = 0; i < STRATEGIESNUM; ++i)
		{
			cin >> playersCode[i];
			temp += playersCode[i];
		}
		if (temp == population) break;
		//~ cout << temp;
		
		// Error-Handling
		cout << "[ERROR] Difference between two inputs of amount of population. \n\n";
	}
	
	/*
	 * Cycle:
	 * 1. Battle
	 * 2. Eliminate lowest 5 players
	 * 3. Clone 5 top players into the game
	 * 4. Order the player in ascending order
	 */
	
	
	
	
	return 0;
}
