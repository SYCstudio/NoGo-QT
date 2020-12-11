#include "chessboardbase.h"

chessboardBase::chessboardBase(QWidget *parent,int size) : QWidget(parent)
{
    memset(boardStatus, -1, sizeof(boardStatus));
    turncnt = 0;

    //initialize buttons and labels
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            boardButton[i][j] = new QPushButton();
            boardButton[i][j] -> setFixedSize(size, size);
        }

    //initialize layout;
    boardLayout = new QGridLayout();
    boardLayout -> setSpacing(0);
    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) boardLayout -> addWidget(boardButton[i][j], i, j);
    setLayout(boardLayout);

    //initialize connect
    //qDebug() << "A";
    QSignalMapper *mapForBoard = new QSignalMapper();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            connect(boardButton[i][j], SIGNAL(clicked()), mapForBoard, SLOT(map()));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            mapForBoard -> setMapping(boardButton[i][j], i*9+j);
    connect(mapForBoard, SIGNAL(mapped(int)), this, SLOT(click(int)));

    dsu = new disjointSetUnion(81);

    return;
}
int chessboardBase::getTurncnt()
{
    return turncnt;
}
int chessboardBase::check(int x, int y, int opt)
{
    if (outBd(x, y)) {
        if (opt) QMessageBox::warning(this, tr("Warning!"), tr("Invalid position!"), QMessageBox::Ok);
        return false;
    }
    if (boardStatus[x][y] != -1) {
        if (opt) QMessageBox::warning(this, tr("Warning!"), tr("This position has been filled."), QMessageBox::Ok);
        return false;
    }
    if (turncnt == 0 && x == 4 && y == 4) {
        if (opt) QMessageBox::warning(this, tr("Warning!"), tr("You cannot select the middle position at first step."), QMessageBox::Ok);
        return false;
    }

    int air = 0, flag = 1, col = turncnt & 1;
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (boardStatus[xx][yy] == -1) ++air;
        else if (boardStatus[xx][yy] == col) {
            int anc = dsu -> getfa(id(xx, yy));
            air += (Mark[anc] ^ 1) * Air[anc] - 1;
            Mark[anc] = 1;
        }
        else if (boardStatus[xx][yy] == (col ^ 1)) {
            --Air[dsu -> getfa(id(xx, yy))];
            if (Air[dsu -> getfa(id(xx, yy))] == 0) flag = 0;
        }
    }
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy)) continue;
        if (boardStatus[xx][yy] == (col ^ 1)) ++Air[dsu -> getfa(id(xx, yy))];
        else if (boardStatus[xx][yy] == col) Mark[dsu -> getfa(id(xx, yy))] = 0;
    }
    qDebug() << air << flag;
    if (air * flag == 0) return -1;
    return 1;
}
void chessboardBase::disableAllGrid()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            //qDebug() << boardButton[i][j] -> isEnabled();
            disableBackup[i][j] = boardButton[i][j] -> isEnabled();
            boardButton[i][j] -> setEnabled(0);
        }
    return;
}
void chessboardBase::restoreAllGrid()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            boardButton[i][j] -> setEnabled(disableBackup[i][j]);
    return;
}
void chessboardBase::click(int xy, int opt)
{
    //qDebug() << xy << opt;
    disableAllGrid();
    int x = xy / 9, y = xy % 9;
    if (x == -1 && y == -1) {
        restoreAllGrid(); return;
    }
    //qDebug() << x << y ;
    int checkRet = check(x, y, opt);
    if (checkRet == 0) {
        restoreAllGrid();
        return;
    }

    restoreAllGrid();
    int col = turncnt & 1;

    boardButton[x][y] -> setEnabled(0);
    boardStatus[x][y] = col;

    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy) || boardStatus[xx][yy] == -1) continue;
        --Air[dsu -> getfa(id(xx, yy))];
    }
    int air = 0, finalanc = id(x, y);
    for (int f = 0; f < 4; f++) {
        int xx = x + Fx[f], yy = y + Fy[f];
        if (outBd(xx, yy) || boardStatus[xx][yy] == (col ^ 1)) continue;
        if (boardStatus[xx][yy] == -1) {
            ++air; continue;
        }
        int anc = dsu -> getfa(id(xx, yy));
        if (anc == finalanc) continue;
        air += Air[anc];
        finalanc = dsu -> merge(anc,finalanc);
    }
    Air[finalanc] = air;

    turncntPlus();
    if (col) boardButton[x][y] -> setStyleSheet("background-color: black");
    else boardButton[x][y] -> setStyleSheet("background-color:white");

    qDebug() << checkRet ;
    if (checkRet == -1) {
        emit gameEnd(turncnt & 1);
    }
    return;
}

void chessboardBase::turncntPlus()
{
    //qDebug() << "get-in turncntPlus";
    ++turncnt;
    emit turncntChanged();
}
