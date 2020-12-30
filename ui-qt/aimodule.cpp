#include "aimodule.h"

int myrandomlib::getInt(int upper)
{
    int key = rnd();
    key = (key % upper + upper) % upper;
    return key;
}

aimodule::aimodule(int level, QWidget *parent) : QWidget(parent)
{
    Level = level;
}

pair<int, int> aimodule::getPos(vector<pair<int, int> > Bd) {
    if (Level == 1) return airandom::getPos(Bd);
    if (Level == 2) return aigreedy::getPos(Bd);
    if (Level == 3) return aimcts::getPos(Bd);
}

namespace airandom {
    nogochessboard * data = nullptr;//new nogochessboard(nullptr, 0);
}

pair<int, int> airandom::getPos(vector<pair<int, int> > Bd)
{
    //qDebug() << "RANDOM";

    if (data == nullptr) data = new nogochessboard(nullptr, 0);
    else data -> reset();

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

    int sz = Pos.size(), id = myrandomlib::getInt(sz);
    //qDebug() << "pos:" << Pos[id].first << Pos[id].second;

    return Pos[id];
}

namespace aigreedy {
    nogochessboard *data = nullptr;//nogochessboard(nullptr, 0);
}

pair<int, int> aigreedy::getPos(vector<pair<int, int> > Bd)
{
    //qDebug() << "GREEDY" ;

    if (data == nullptr) data = new nogochessboard(nullptr, 0);
    else data -> reset();

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
        int sz = iPos.size(), id = myrandomlib::getInt(sz);
        //qDebug() << id;
        //qDebug() << id << iPos[id].first << iPos[id].second << data -> check(iPos[id].first, iPos[id].second);
        return iPos[id];
    }

    int key = myrandomlib::getInt(sum) + 1;
    //qDebug() << "key and sum" << key << sum;
    for (int i = 0, sz = Pos.size(), tot = 0; i < sz; i++) {
        tot += Value[i];
        if (tot >= key) {
            //qDebug() << Pos[i].first << Pos[i].second << data -> check(Pos[i].first, Pos[i].second);
            return Pos[i];
        }
    }
}

namespace aimcts {
    int nodecnt, playcnt;
    NodeData T[1010000];
    nogochessboard * data = nullptr;//= new nogochessboard(nullptr, 0);
}

int aimcts::getId(int x, int y){return x * 9 + y;}
int aimcts::getX(int id){return id / 9;}
int aimcts::getY(int id){return id % 9;}

pair<int, int> aimcts::getPos(vector<pair<int, int> > Bd)
{
    if (data == nullptr) data = new nogochessboard(nullptr, 0);
    else data -> reset();
    nodecnt = playcnt = 0;
    getNewnode();//initialize root

    int turn = Bd.size();
    for (int i = 0; i < turn; i++) data -> place(Bd[i].first, Bd[i].second);

    //双方可行落子位置
    vector<int> my, opp;
    for (int x = 0; x < 9; x++)
        for (int y = 0; y < 9; y++) {
            if (data -> check(x, y) == 1) my.push_back(getId(x, y));
            if (data -> checkopp(x, y) == 1) opp.push_back(getId(x, y));
        }
    //qDebug() << my.size() << opp.size();
    if (my.size() == 0) {
        for (int x = 0; x < 9; x++)
            for (int y = 0; y < 9; y++)
                if (data -> check(x, y) != 0) return make_pair(x, y);
    }

    //开始 MTCS
    while (playcnt < MCTS_TIMES) dfs(1, 1);
    qDebug() << nodecnt ;

    int ansvisit = 0, ans;
    for (map<int, int>::iterator it = T[1].Son.begin(); it != T[1].Son.end(); it++)
        if (ansvisit < T[(*it).second].visit) ansvisit = T[(*it).second].visit, ans = (*it).first;
    return make_pair(getX(ans), getY(ans));
}

int aimcts::getNewnode() {
    ++nodecnt;
    T[nodecnt].clear();
    return nodecnt;
}

int aimcts::dfs(int depth, int u) {
    Q_ASSERT(u > 0);
    //qDebug() << depth << u << nodecnt << T[u].visit;
    ++playcnt;
    if (T[u].visit == 0) { //未探索过，开始随机走子
        vector<int> Pos[2];

        for (int x = 0; x < 9; x++)
            for (int y = 0; y < 9; y++) {
                if (data -> check(x, y) == 1) Pos[0].push_back(getId(x, y));
                if (data -> checkopp(x, y) == 1) Pos[1].push_back(getId(x, y));
            }
        T[u].P = Pos[0];

        int backup_turn = data -> getTurncnt(), is_my_win = 0;
        while (1) {
            int placeable = 0;
            while (1) {
                int sz = Pos[is_my_win].size();
                if (sz == 0) break;
                int id = myrandomlib::getInt(sz);
                std::swap(Pos[is_my_win][id], Pos[is_my_win][sz-1]);
                id = Pos[is_my_win][sz-1];Pos[is_my_win].pop_back();
                int x = getX(id), y = getY(id);

                if (data -> check(x, y) == 1) {
                    data -> place(x, y);
                    placeable = 1;
                    break;
                }
            }

            if (placeable == 0) {
                T[u].wint += is_my_win;
                break;
            }

            is_my_win ^= 1;
            //My.swap(Opp);
            //std::swap(My, Opp);
        }
        while (data -> getTurncnt() > backup_turn) data -> undo();
        ++T[u].visit;
        return is_my_win;
    }

    if (T[u].P.size() == 0) {//该节点已经被完全探索
        if (T[u].Son.size() == 0) {
            T[u].visit ++;
            return 0;
        }
        double mxvalue = -inf;
        int son = -1;
        for (map<int, int>::iterator it = T[u].Son.begin(); it != T[u].Son.end(); it++) {
            int v = (*it).second;
            double value = 1.0 * T[v].wint / T[v].visit + BALANCE_VALUE * sqrt(log(T[u].visit) / T[v].visit);
            if (value > mxvalue) mxvalue = value, son = (*it).first;
        }
        //qDebug() << "place:" << getX(son) << getY(son) << T[u].Son[son];
        Q_ASSERT(son != -1);

        data -> place(getX(son), getY(son));
        int ret = dfs(depth + 1, T[u].Son[son]);
        data -> undo();

        T[u].visit++;
        T[u].wint += ret ^ 1;
        return ret ^ 1;
    }

    //该节点存在未探索的子节点
    int sz = T[u].P.size();
    int id = myrandomlib::getInt(sz);
    std::swap(T[u].P[id], T[u].P[sz-1]);
    id = T[u].P[sz-1];T[u].P.pop_back();

    T[u].Son[id] = getNewnode();
    //qDebug() << "place new:" << getX(id) << getY(id) << T[u].Son[id];
    data -> place(getX(id), getY(id));
    int ret = dfs(depth + 1, T[u].Son[id]);
    data -> undo();

    T[u].visit++;
    T[u].wint += ret ^ 1;
    return ret ^ 1;
}
