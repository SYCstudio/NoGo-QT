#ifndef AIMODULE_H
#define AIMODULE_H

#include <QWidget>
#include <random>
#include <ctime>
#include <vector>
#include "nogochessboard.h"

using std::vector;
using std::pair;
using std::make_pair;


namespace myrandomlib
{
    static std::mt19937 rnd(time(0));
};

class aimodule : public QWidget
{
    Q_OBJECT
public:
    int Level;
    explicit aimodule(int level, QWidget *parent = nullptr);
    pair<int, int> getPos(vector<pair<int, int> > Bd);
};

namespace airandom {
    pair<int, int> getPos(vector<pair<int, int> > Bd);
};

namespace aigreedy {
    const int PRE_VALUE[9][9] = {{1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 1, 1}};
    const int DIAG_VALUE = 10000;
    const int GRID_VALUE[4] = {0, 1000, 10000, 7000000};
    const int GRID_VALUE2[4] = {0, 3000, 70000, 15000000};
    pair<int, int> getPos(vector<pair<int, int> > Bd);
}

#endif // AIMODULE_H
