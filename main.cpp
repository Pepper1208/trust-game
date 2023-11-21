#include ".\headers\singleGame.h"

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

int main()
{
	// For a single cycle with 2 strategies
	
	startCycle(15, 5, 1);
	
	return 0;
}
