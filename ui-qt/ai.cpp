#include "ai.h"
std::pair<int, int> AI::AI(std::vector<std::pair<int, int> > Bd)
{
    return std::make_pair(rand() % 9, rand() % 9);
}

void AI::INIT() {
    srand(time(0));
    return;
}
