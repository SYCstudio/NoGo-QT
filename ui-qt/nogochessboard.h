#ifndef NOGOCHESSBOARD_H
#define NOGOCHESSBOARD_H

#include <vector>
#include "disjointsetunion.h"

class nogochessboard : public disjointSetUnion
{
public:
    nogochessboard();
private:
    const int Fx[4] = {-1, 0, 1, 0};
    const int Fy[4] = {0, 1, 0, -1};
    int Air[81], Mark[81];
    int boardStatus[9][9];
    int turncnt, clickX[81], clickY[81];

    void turncntPlus();
    bool outBd(int x, int y) {
        return x > 8 || x < 0 || y > 8 || y < 0;
    }
    bool inBd(int x, int y) {
        return !outBd(x, y);
    }
    int id(int x, int y) {
        return x * 9 + y;
    }
};

#endif // NOGOCHESSBOARD_H
