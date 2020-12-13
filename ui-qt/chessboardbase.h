#ifndef CHESSBOARDBASE_H
#define CHESSBOARDBASE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <QSignalMapper>
#include <algorithm>
#include "disjointsetunion.h"

class chessboardBase : public QWidget
{
    Q_OBJECT
public:
    explicit chessboardBase(QWidget *parent = nullptr, int size = 50);
    int getTurncnt() {
        return turncnt;
    }
    int getNowpoint() {
        return nowpoint;
    }
    int check(int x, int y,int opt = 0);//opt == 0:disable msg prompt;else show msg

    disjointSetUnion *dsu;

private:
    const int Fx[4] = {-1, 0, 1, 0};
    const int Fy[4] = {0, 1, 0, -1};
    int isDisableGrid;
    int boardStatus[9][9], turncnt, Air[9 * 9], Mark[9 * 9];
    int clickX[81], clickY[81], nowpoint;
    QPushButton *boardButton[9][9];
    QGridLayout *boardLayout;

    void disableAllGrid();
    void restoreAllGrid();
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
    void changeNowpoint(int crt);

signals:
    void turncntChanged();
    void gameEnd(int opt);
    void nowpointChanged();

public slots:
    void click(int xy, int opt = 1);
    void backTo(int round);
};

#endif // CHESSBOARDBASE_H
