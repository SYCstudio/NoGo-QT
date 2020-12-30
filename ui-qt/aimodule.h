#ifndef AIMODULE_H
#define AIMODULE_H

#include <QWidget>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>
#include <map>
#include "nogochessboard.h"

using std::vector;
using std::pair;
using std::make_pair;
using std::map;


namespace myrandomlib
{
    static std::mt19937 rnd(time(0));
    int getInt(int upper);
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
    nogochessboard * data = new nogochessboard(nullptr, 0);
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
    nogochessboard * data = new nogochessboard(nullptr, 0);
    pair<int, int> getPos(vector<pair<int, int> > Bd);
}

namespace aimcts {
    const double BALANCE_VALUE = 1.0 / sqrt(2);
    const int MCTS_TIMES = 100;
    class NodeData {
    public:
        int wint, visit, fa;
        map<int, int> Son;
        void clear() {
            wint = visit = fa = 0;
            Son.clear();
            return;
        }
    };

    int nodecnt;
    NodeData T[1010000];
    nogochessboard * data = new nogochessboard(nullptr, 0);
    vector<int> My, Opp;

    int getId(int x, int y){return x * 9 + y;}
    int getX(int id){return id/9;}
    int getY(int id){return id%9;}
    pair<int, int> getPos(vector<pair<int, int> > Bd);
    int getNewnode();
    int dfs(int depth, int u);
}

#endif // AIMODULE_H
