#include "aimodule.h"

pair<int, int> airandom::getPos(vector<pair<int, int> > Bd)
{
    //qDebug() << "RANDOM";

    nogochessboard *data = new nogochessboard(0);

    int turn = Bd.size();
    for (int i = 0; i < turn; i++) data -> place(Bd[i].first, Bd[i].second);

    vector<pair<int, int> > Pos;
    for (int x = 0; x < 9; x++)
        for (int y = 0; y < 9; y++)
            if (data -> check(x, y) == 1) Pos.push_back(make_pair(x, y));

    if (Pos.size() == 0) {
        for (int x = 0; x < 9; x++)
            for (int y = 0; y < 9; y++)
                if (data -> check(x, y) != 0) return make_pair(x, y);
    }

    int id = myrandomlib::rnd(), sz = Pos.size();
    id = (id % sz + sz) % sz;
    //qDebug() << "pos:" << Pos[id].first << Pos[id].second;

    return Pos[id];
}

pair<int, int> aigreedy::getPos(vector<pair<int, int> > Bd) {
    //qDebug() << "GREEDY" ;

    nogochessboard * data = new nogochessboard(0);

    int turn = Bd.size(), col = (turn + 1) & 1;
    for (int i = 0; i < turn; i++) data -> place(Bd[i].first, Bd[i].second);

    vector<pair<int, int> > Pos, iPos;
    vector<int> Value;
    int sum = 0;

    for (int x = 0; x < 9; x++)
        for (int y = 0; y < 9; y++)
            if (data -> check(x, y) == 1) {
                if (data -> checkopp(x, y) == -1) {
                    iPos.push_back(make_pair(x, y));
                    continue;
                }
                int value = PRE_VALUE[x][y];
                //四角
                if (data -> getPositionColor(0, 0) == -1) {
                    if (x == 0 && y == 1) value += DIAG_VALUE;
                    if (x == 1 && y == 0) value += DIAG_VALUE;
                }
                if (data -> getPositionColor(0, 8) == -1) {
                    if (x == 0 && y == 7) value += DIAG_VALUE;
                    if (x == 1 && y == 8) value += DIAG_VALUE;
                }
                if (data -> getPositionColor(8, 0) == -1) {
                    if (x == 7 && y == 0) value += DIAG_VALUE;
                    if (x == 8 && y == 1) value += DIAG_VALUE;
                }
                if (data -> getPositionColor(8, 8) == -1) {
                    if (x == 7 && y == 8) value += DIAG_VALUE;
                    if (x == 8 && y == 7) value += DIAG_VALUE;
                }
                //制造网格
                value += GRID_VALUE[
                        (data -> checkPositionColor(x+1, y-1, col)
                         & data -> checkPositionColor(x, y-1, -1)
                         & data ->checkPositionColor(x-1, y-1, col))
                        +(data -> checkPositionColor(x-1, y-1, col)
                          & data -> checkPositionColor(x-1, y, -1)
                          & data ->checkPositionColor(x-1, y+1, col))
                        +(data -> checkPositionColor(x-1, y+1, col)
                          & data -> checkPositionColor(x, y+1, -1)
                          & data ->checkPositionColor(x+1, y+1, col))
                        +(data -> checkPositionColor(x+1, y+1, col)
                          & data -> checkPositionColor(x+1, y, -1)
                          & data ->checkPositionColor(x+1, y-1, col))];
                value += GRID_VALUE2[
                        (data -> checkPositionColor(x, y-2, col)
                         & data -> checkPositionColor(x-1, y-1, col)
                         & data -> checkPositionColor(x+1, y-1, col)
                         & data -> checkPositionColor(x, y-1, -1))
                        +(data -> checkPositionColor(x-2, y, col)
                          & data -> checkPositionColor(x-1, y-1, col)
                          & data -> checkPositionColor(x-1, y+1, col)
                          & data -> checkPositionColor(x-1, y, -1))
                        +(data -> checkPositionColor(x, y+2, col)
                          & data -> checkPositionColor(x-1, y+1, col)
                          & data -> checkPositionColor(x+1, y+1, col)
                          & data -> checkPositionColor(x, y+1, -1))
                        +(data -> checkPositionColor(x+2, y, col)
                          & data -> checkPositionColor(x+1, y-1, col)
                          & data -> checkPositionColor(x+1, y+1, col)
                          & data -> checkPositionColor(x+1, y, -1))];
                Pos.push_back(make_pair(x, y));
                Value.push_back(value);
                sum += value;
            }

    //qDebug() << Pos.size() << iPos.size();
    if (Pos.size() + iPos.size() == 0) {
        //qDebug() << "No choice";
        for (int x = 0; x < 9; x++)
            for (int y = 0; y < 9; y++)
                if (data -> check(x, y) != 0) return make_pair(x, y);
    }

    if (Pos.size() == 0){
        int id = myrandomlib::rnd(), sz = iPos.size();
        //qDebug() << id;
        id = (id % sz + sz) % sz;
        //qDebug() << id << iPos[id].first << iPos[id].second << data -> check(iPos[id].first, iPos[id].second);
        return iPos[id];
    }

    int key = myrandomlib::rnd();
    key = (key % sum + sum) % sum + 1;
    //qDebug() << "key and sum" << key << sum;
    for (int i = 0, sz = Pos.size(), tot = 0; i < sz; i++) {
        tot += Value[i];
        if (tot >= key) {
            //qDebug() << Pos[i].first << Pos[i].second << data -> check(Pos[i].first, Pos[i].second);
            return Pos[i];
        }
    }
}
