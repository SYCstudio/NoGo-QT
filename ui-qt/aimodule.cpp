#include "aimodule.h"

aimodule::aimodule(int level, QWidget *parent) : QWidget(parent)
{
    Level = level;
}

pair<int, int> aimodule::getPos(vector<pair<int, int> > Bd) {
    if (Level == 1) return airandom::getPos(Bd);
}

pair<int, int> airandom::getPos(vector<pair<int, int> > Bd)
{
    //qDebug() << "RND" ;

    nogochessboard *data = new nogochessboard(nullptr, 0);

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

    std::mt19937 rnd(time(0));
    int id = rnd(), sz = Pos.size();
    id = (id % sz + sz) % sz;

    //qDebug() << "pos:" << Pos[id].first << Pos[id].second;

    return Pos[id];
}
