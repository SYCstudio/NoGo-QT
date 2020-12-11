#include "chessboardbase.h"

chessboardBase::chessboardBase(QWidget *parent,int size) : QWidget(parent)
{
    memset(boardStatus, -1, sizeof(boardStatus));
    turncnt = 0;

    //initialize buttons and labels
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            boardButton[i][j] = new chessGrid();
            boardButton[i][j] -> setFixedSize(size, size);
        }

    //initialize layout;
    boardLayout = new QGridLayout();
    boardLayout -> setSpacing(0);
    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) boardLayout -> addWidget(boardButton[i][j], i, j);
    setLayout(boardLayout);

    //initialize connect
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            connect(boardButton[i][j], SIGNAL(clicked()), boardButton[i][j], SLOT(setMark()));
            connect(boardButton[i][j], SIGNAL(clicked()), this, SLOT(click()));
        }

    return;
}
int chessboardBase::getTurncnt()
{
    return turncnt;
}
bool chessboardBase::check(int x, int y, int opt)
{
    if (x > 8 || x < 0 || y > 8 || y > 8) {
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
    return true;
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
void chessboardBase::click(int opt)
{
    disableAllGrid();
    int x = -1, y = -1;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (boardButton[i][j] -> getMark()) {
                x = i; y = j;
            }
    if (x == -1 && y == -1) {
        restoreAllGrid(); return;
    }
    qDebug() << x << y ;
    boardButton[x][y] -> setMark(0);
    if (check(x, y, opt) == false) {
        restoreAllGrid();
        return;
    }
    restoreAllGrid();
    boardButton[x][y] -> setEnabled(0);
    ++turncnt;
    if (turncnt & 1) boardButton[x][y] -> setStyleSheet("background-color: black");
    else boardButton[x][y] -> setStyleSheet("background-color:white");
    return;
}
