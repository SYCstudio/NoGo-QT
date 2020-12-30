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
    static std::mt19937 rnd(0);//rnd(time(0));
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

namespace aimcts {
    const double inf = 1e10;
    const double BALANCE_VALUE = sqrt(2);
    const int MCTS_TIMES = 1000;
    class NodeData {
    public:
        int wint, visit, fa;
        //int Son[81];
        map<int, int> Son;
        vector<int> P;
        void clear() {
            //memset(Son, -1, sizeof(Son));
            Son.clear();
            wint = visit = fa = 0;
            P.clear();
            return;
        }
    };

    int getId(int x, int y);
    int getX(int id);
    int getY(int id);
    pair<int, int> getPos(vector<pair<int, int> > Bd);
    int getNewnode();
    int dfs(int depth, int u);
}
//*/

#endif // AIMODULE_H
