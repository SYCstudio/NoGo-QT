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
    int getTurncnt();
    int check(int x, int y,int opt = 0);//opt == 0:disable msg prompt;else show msg
    void turncntPlus();
    disjointSetUnion *dsu;

private:
    const int Fx[4] = {-1, 0, 1, 0};
    const int Fy[4] = {0, 1, 0, -1};
    int boardStatus[9][9], turncnt, Air[9 * 9], Mark[9 * 9];
    QPushButton *boardButton[9][9];
    QGridLayout *boardLayout;

    int disableBackup[9][9];

    void disableAllGrid();
    void restoreAllGrid();
    bool outBd(int x, int y) {
        return x > 8 || x < 0 || y > 8 || y < 0;
    }
    bool inBd(int x, int y) {
        return !outBd(x, y);
    }
    int id(int x, int y) {
        return x * 9 + y;
    }

signals:
    void turncntChanged();
    void gameEnd(int opt);

public slots:
    void click(int xy, int opt = 1);
};

#endif // CHESSBOARDBASE_H
