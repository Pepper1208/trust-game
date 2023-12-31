#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <utility>

std::pair<int, int> startCycle(int gameSize, int code1, int code2, bool showProgress);
std::pair<int, int> fullGame(int gameSize, int code1, int code2, int p1[], int p2[], bool showProgress);

#endif /* SINGLEGAME_H */
