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
}

pair<int, int> airandom::getPos(vector<pair<int, int> > Bd)
{
    //qDebug() << "RANDOM";

    data -> reset();

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

pair<int, int> aigreedy::getPos(vector<pair<int, int> > Bd)
{
    //qDebug() << "GREEDY" ;

    data -> reset();

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

pair<int, int> aimcts::getPos(vector<pair<int, int> > Bd)
{
    data -> reset();
    nodecnt = 0;
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

    //开始 MTCS
    for (int _times = 0; _times < MCTS_TIMES; _times++) {
        My = my;
        Opp = opp;
        dfs(1, 1);
    }

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
    if (T[u].visit == 0) { //未探索过，开始随机走子
        T[u].visit ++;
        int backup_turn = data -> getTurncnt(), is_my = 0;
        while (1) {
            int placeable = 0;
            while (!(placeable == 1 || My.size() == 0)) {
                int sz = My.size();
                int id = myrandomlib::getInt(sz);
                std::swap(My[id], My[sz-1]);
                id = My[sz-1];My.pop_back();
                int x = getX(id), y = getY(id);

                if (data -> check(x, y) == 1) {
                    data -> place(x, y);
                    placeable = 1;
                }
            }

            if (placeable == 0) {
                T[u].wint += is_my;
                break;
            }

            is_my ^= 1;
            My.swap(Opp);
        }
        while (data -> getTurncnt() > backup_turn) data -> undo();
        return is_my;
    }

    //已探索过，检查是否有未扩展的子节点
    int pos = -1;
    vector<int> buf, unvisit;
    for (int i = 0, sz = My.size(); i < sz; i++)
        if (data -> check(getX(My[i]), getY(My[i])) == 1) {
            buf.push_back(My[i]);
            if (T[u].Son.count(My[i]) == 0) unvisit.push_back(My[i]);
        }
}
