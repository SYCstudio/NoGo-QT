#ifndef AI_H
#define AI_H

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

namespace AI {
    void INIT();
    std::pair<int, int> AI(std::vector<std::pair<int, int> > Bd);
}

#endif // AI_H
