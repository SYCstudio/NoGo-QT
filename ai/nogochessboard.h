#ifndef NOGOCHESSBOARD_H
#define NOGOCHESSBOARD_H

#include <vector>
#include <cstring>
#include <stack>
#include "disjointsetunion.h"

class nogochessboard
{
public:
    nogochessboard(int show_msg);

    int getTurncnt() {return Turncnt;}

    void reset();
    int check(int x, int y,int show_msg = -1);//返回值：0 不合法；1 合法；-1 合法但出现气为 0
    int checkopp(int x, int y);
    void place(int x, int y,int show_msg = -1);
    std::vector<std::pair<int, int> > getBoard(int show_turn = -1);
    int isGameEnded(){return is_game_end;}
    bool outBd(int x, int y) {return x > 8 || x < 0 || y > 8 || y < 0;}
    bool inBd(int x, int y) {return !outBd(x, y);}
    int getPositionColor(int x, int y) {return BoardStatus[id(x, y)];}
    int checkPositionColor(int x, int y, int col);

private:
    int SHOW_MSG;
    const int Fx[4] = {-1, 0, 1, 0};
    const int Fy[4] = {0, 1, 0, -1};
    disjointSetUnion *dsu;//并查集维护气
    int Air[81];//保存气
    int BoardStatus[81];//棋盘
    int Turncnt, PlaceX[90], PlaceY[90];//回合，分别下的位置
    int TopPositionRecord[90];
    bool is_game_end;
    int AirRec[90][4], AncRec[90][4];

    int id(int x, int y) { return x * 9 + y;}
    int getX(int x) {return x/9;}
    int getY(int x) {return x%9;}

    void turncntPlus();
    void turncntMinus();

    //void gameEnded(int winner);//0-white,1-black
    //void turncntChanged();

public:
    void undo();
};

#endif // NOGOCHESSBOARD_H
