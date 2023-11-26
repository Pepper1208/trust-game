#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <utility>

void printCodeInstruction();

std::pair<int, int> startCycle(int gameSize, int code1, int code2);
std::pair<int, int> fullGame(int gameSize, int code1, int code2, int p1[], int p2[], bool showProgress);

#endif /* SINGLEGAME_H */
